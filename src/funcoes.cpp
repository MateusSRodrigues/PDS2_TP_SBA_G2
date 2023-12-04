#include <vector>
#include <unistd.h>
#include <iostream>

#include "funcoes.h"

#ifdef _WIN32
    // Código específico para Windows
    #define CLEAR_SCREEN "cls"
    #include <conio.h>
    #define PEGCHAR _getch()

#elif __linux__
    // Código específico para Linux
    #define CLEAR_SCREEN "clear"
    #include <termios.h>
    #define PEGCHAR getch()

    char getch() {
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror ("tcsetattr ~ICANON");
    return buf;
}
#endif

void cadastrar(Biblioteca* b){
    string nome, telefone, id, senha;
    cin.clear();
    cout << "Nome: ";
    getline(cin, nome);
    while (any_of(nome.begin(), nome.end(), [](char c) { return !isalpha(c) && !isspace(c); }))
    {
        cout << "\033[1;31mO nome deve conter apenas letras.\033[0m" << endl;
        cout << "\033[1;31mDigite o nome novamente.\033[0m" << endl;
        //throw invalid_argument();
        cout << "Nome: ";
        getline(cin, nome);
    }
    
    cout << "Telefone: ";
    cin >> telefone;
    while (telefone.size() != 11 || !all_of(telefone.begin(), telefone.end(), [](char c) { return isdigit(c); }))
    {
        cout << "\033[1;31mO telefone deve ter 11 digitos e conter apenas numeros.\033[0m" << endl;
        cout << "\033[1;31mDigite o telefone novamente.\033[0m" << endl;
        cout << "Telefone: ";
        cin >> telefone;
    }
    
    cout << "Id: ";
    cin >> id;
    while ((id.size() != 5 && id.size() != 7 && id.size() != 9)
            || (!all_of(id.begin(), id.end(), [](char c) { return isdigit(c); }))
            || (b->get_usuario(id) != nullptr or b->get_funcionario(id) != nullptr))
    {
        if(id.size() != 5 && id.size() != 7 && id.size() != 9){
            cout << "\033[1;31mO ID deve ter 5, 7 ou 9 digitos.\033[0m" << endl;
            cout << "\033[1;31mDigite o id novamente.\033[0m" << endl;
            cout << "Id: ";
        }else if(!all_of(id.begin(), id.end(), [](char c) { return isdigit(c); })){
            cout << "\033[1;31mA identificacao deve conter apenas numeros.\033[0m" << endl;
            cout << "\033[1;31mDigite o id novamente.\033[0m" << endl;
            cout << "Id: ";
        }else if((b->get_usuario(id) != nullptr or b->get_funcionario(id) != nullptr)){
            cout << "\033[1;31mEsta Identificacao ja esta em uso.\033[0m" << endl;
            cout << "\033[1;31mDigite o id novamente.\033[0m" << endl;
            cout << "Id: ";
        }
        cin >> id;
    }

    cout << "Senha: ";
    cin >> senha;
    while (senha.size() < 4 || senha.size() > 8 || !all_of(senha.begin(), senha.end(), [](char c) {return isalnum(c);}))
    {
        cout << "\033[1;31mA senha deve ter entre 4 e 8 caracteres alfanumericos.\033[0m" << endl;
        cout << "\033[1;31mDigite a senha novamente.\033[0m" << endl;
        cout << "Senha: ";
        cin >> senha;
    }

    if (id.size() == 5) {/// funcionario
        string turno;
        cout << "Turno de trabalho [1(manha), 2(tarde) ou 3(noite)]: ";
        cin >> turno;
        while (turno != "1" && turno != "2" && turno !="3")
        {
            cout << "\033[1;31mturno invalido, permitido apenas os numerais 1,2 e 3.\033[0m" << endl;
            cout << "\033[1;31mDigite o turno novamente.\033[0m" << endl;
            cout << "Turno de trabalho [1(manha), 2(tarde) ou 3(noite)]: ";
            cin >> turno;
        }
        if(turno == "1"){ turno = "manha";}
        else if(turno == "2"){turno = "tarde";}
        else if(turno == "3"){turno = "noite";}
        b->criar_funcionario(nome, senha, telefone, id, turno);
        cout << "\033[32mConta de funcionario criada com sucesso!\033[0m" << endl;
    }
    if (id.size() == 7 or id.size() == 9) { /// prof ou aluno.
        b->criar_usuario(nome, senha, telefone, id);
        if(id.size() == 9) {
            cout << "\033[32mConta de usuario estudante criada com sucesso!\033[0m" << endl;
        }else if (id.size() == 7){
            cout << "\033[32mConta de usuario professor criada com sucesso!\033[0m" << endl;
        }
    }
};

string menu2(vector<string>& opcao,  vector<string>& cabecalho){
    int c = 0;
    for (int i = 0; i < cabecalho.size(); i++) {
        cout << cabecalho[i];
    }
    cout << endl << "------------------------------"<< endl << "\033[34m"<< "->"<< "\033[0m";
    for (int i = 0; i < opcao.size(); i++) {
        if(i == 0){
            cout  << "\033[34m"<< opcao[i] << "\033[0m" << endl;
        }else
            cout  <<  opcao[i]  << endl;
    }
    cout << "===================================="<< endl << "===================================="<< endl;
    while (auto n = PEGCHAR) {
        system(CLEAR_SCREEN);
        switch (n) {
            case 's':
                c++;  //altera contador de click, desc a seta
                break;

            case 'w':
                c--;  //altera contador de click,  sub a seta
                break;

            case 'd':   //escolhe opçao
                if (c==0) {
                    return opcao[0];
                }else
                    return opcao[c % opcao.size()];
        }

        for (int i = 0; i < opcao.size(); i++) {    //loop imprime a lista de opçoes
            if (i == 0) {                           // para i=0 limpa tela e impime cabeçalho
                for (int i = 0; i < cabecalho.size(); i++) {
                    cout << cabecalho[i];
                }
                cout << endl << "------------------------------"<< endl;
            }
            if (i == c % opcao.size()) {        /// calcula e imprime seta
                cout << "->";
                cout  <<  "\033[34m" << opcao[i] << "\033[0m"  << endl;
            } else{                         /// imprime restante
                cout << opcao[i]<< endl;
            }
            if (i == opcao.size()-1) {
                cout << "===================================="<< endl << "===================================="<< endl;
            }
        }
    }
    return "nehuma das opcoes";
}

PedidoReserva* menu3(vector<PedidoReserva*>& opcao,  vector<string>& cabecalho, vector<int>& quant){
    //char n;
    int c = 0;
    string disponibilidade;
    for (int i = 0; i < cabecalho.size(); i++) {
        cout << cabecalho[i];
    }
    cout << endl << "------------------------------"<< endl << "->";

    for (int i = 0; i < opcao.size() ; i++) {
        if(i == 0){
            cout  << "\033[34m" << "Usuario: " <<  opcao[i]->identificacao_usuario << " pediu reserva do livro: "<< opcao[i]->livro_pedido->get_nome()<< "- disponiveis: "<< quant[i] <<  "\033[0m" << endl;
        }else
            cout  << "Usuario: " <<  opcao[i]->identificacao_usuario << " pediu reserva do livro: "<< opcao[i]->livro_pedido->get_nome()<< " - disponiveis: "<< quant[i] << endl;
    }
    cout << "===================================="<< endl << "====================================" << endl;
    while (auto n = PEGCHAR) {
        system(CLEAR_SCREEN);
        switch (n) {
            case 's':
                c++;  //altera contador de click, desc a seta
                break;

            case 'w':
                c--;  //altera contador de click,  sub a seta
                break;

            case 'd':  //escolhe opçao
                if (c==0) {
                    return opcao[0];
                }else
                    return opcao[c % opcao.size()];
        }

        for (int i = 0; i < opcao.size(); i++) {   //loop imprime a lista de opçoes
            string disp = "Disponivel.";
            if(opcao[i]->livro_pedido->get_estado_emprestimo()!= "Disponivel"){
                disp = "Indisponivel.";
            }
            if (i == 0) {             // para i=0 limpa tela e impime cabeçalho
                for (int i = 0; i < cabecalho.size(); i++) {
                    cout << cabecalho[i];
                }
                cout << endl << "============================"<< endl;
            }
            if (i == c % opcao.size()) {    // calcula e imprime seta
                cout << "->";
                cout  << "\033[34m" << "Usuario: " << opcao[i]->identificacao_usuario << " pediu reserva do livro: "<< opcao[i]->livro_pedido->get_nome()<< "- disponiveis: "<< quant[i]  << "\033[0m" << endl;

            } else{                // imprime restante
                cout <<"Usuario: " << opcao[i]->identificacao_usuario << " pediu reserva do livro: "<< opcao[i]->livro_pedido->get_nome()<< "- disponiveis: "<< quant[i] << endl;
            }
            if (i == opcao.size()-1) {
                cout << "===================================="<< endl << "===================================="<< endl;
            }
        }
    }
    return nullptr;
}