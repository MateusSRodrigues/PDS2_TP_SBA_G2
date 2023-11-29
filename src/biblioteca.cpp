///
//
// Created by rayda on 02/11/2023.

#include <vector>
#include <unistd.h>
#include <iostream>
//#include <conio.h>

#include "biblioteca.h"

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

string menu2(vector<string>& opcao,  vector<string>& cabecalho){
    //char n;
    int c = 0;
    for (int i = 0; i < cabecalho.size(); i++) {
        cout << cabecalho[i];
    }
    cout << endl << "=================================="<< endl << "\033[34m"<< "->"<< "\033[0m";
    for (int i = 0; i < opcao.size(); i++) {
        if(i == 0){
            cout  << "\033[34m"<< opcao[i] << "\033[0m" << endl;
        }else
            cout  <<  opcao[i]  << endl;
    }
    cout << "###############################"<< endl << "###############################" << endl;
    while (auto n = PEGCHAR) {
        system(CLEAR_SCREEN);
        switch (n) {
            case 's':
                c++;              ///altera contador de click, desc a seta
                break;

            case 'w':
                c--;              ///altera contador de click,  sub a seta
                break;

            //case '/n':
            case 'd':             ///escolhe opçao
                if (c==0) {
                    return opcao[0];
                }else
                    return opcao[c % opcao.size()];
        }

        for (int i = 0; i < opcao.size(); i++) {        ///loop imprime a lista de opçoes
            if (i == 0) {                           /// para i=0 limpa tela e impime cabeçalho
                for (int i = 0; i < cabecalho.size(); i++) {
                    cout << cabecalho[i];
                }
                cout << endl << "=================================="<< endl;
            }
            if (i == c % opcao.size()) {        /// calcula e imprime seta
                cout << "->";
                cout  <<  "\033[34m" << opcao[i] << "\033[0m"  << endl;
            } else{                         /// imprime restante
                cout << opcao[i]<< endl;
            }
            if (i == opcao.size()-1) {
                cout << "#################################"<< endl << "#################################"<< endl;
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
    cout << endl << "============================"<< endl << "->";

    for (int i = 0; i < opcao.size() ; i++) {
        if(i == 0){
            cout  << "\033[34m" << "Usuario: " <<  opcao[i]->identificacao_usuario << " pediu reserva do livro: "<< opcao[i]->livro_pedido->get_nome()<< "- disponiveis: "<< quant[i] <<  "\033[0m" << endl;
        }else
            cout  << "Usuario: " <<  opcao[i]->identificacao_usuario << " pediu reserva do livro: "<< opcao[i]->livro_pedido->get_nome()<< " - disponiveis: "<< quant[i] << endl;
    }
    cout << "###############################"<< endl << "###############################" << endl;
    while (auto n = PEGCHAR) {
        system(CLEAR_SCREEN);
        switch (n) {
            case 's':
                c++;              ///altera contador de click, desc a seta
                break;

            case 'w':
                c--;              ///altera contador de click,  sub a seta
                break;

            //case '\n':
            case 'd':            ///escolhe opçao
                if (c==0) {
                    return opcao[0];
                }else
                    return opcao[c % opcao.size()];
        }

        for (int i = 0; i < opcao.size(); i++) {        ///loop imprime a lista de opçoes
            string disp = "Disponivel.";
            if(opcao[i]->livro_pedido->get_estado_emprestimo()!= "Disponivel"){
                disp = "Indisponivel.";
            }
            if (i == 0) {                           /// para i=0 limpa tela e impime cabeçalho
                for (int i = 0; i < cabecalho.size(); i++) {
                    cout << cabecalho[i];
                }
                cout << endl << "============================"<< endl;
            }
            if (i == c % opcao.size()) {        /// calcula e imprime seta
                cout << "->";
                cout  << "\033[34m" << "Usuario: " << opcao[i]->identificacao_usuario << " pediu reserva do livro: "<< opcao[i]->livro_pedido->get_nome()<< "- disponiveis: "<< quant[i]  << "\033[0m" << endl;

            } else{                         /// imprime restante
                cout <<"Usuario: " << opcao[i]->identificacao_usuario << " pediu reserva do livro: "<< opcao[i]->livro_pedido->get_nome()<< "- disponiveis: "<< quant[i] << endl;
            }
            if (i == opcao.size()-1) {
                cout << "###############################"<< endl << "###############################"<< endl;
            }
        }
    }
    return nullptr;
}
void Biblioteca::criar_usuario(string n, string sen, string t, string id) {
    Usuario *user = new Usuario(n,sen,t,id);
    usuarios.push_back(user);
}
void Biblioteca::criar_funcionario(string n, string sen, string t, string id, string turno) {
    Funcionario *func = new Funcionario(n,sen,t,id,turno);
    funcionarios.push_back(func);
}
void Biblioteca::adicionar_livro(Livro* novo_livro) {
    bool existe = 0 ;    /// Verificar se já existe uma lista com um livro com este nome
    for (auto& lista : todos_livros) {
        for (auto& livro_ptr : lista) {
            if (lista.front()->get_nome() == novo_livro->get_nome()) {   ///se ja existir um livro com esse nome, o livro criado é adicionado ao list dele.
                existe = 1;
                novo_livro->set_link(lista.front()->get_link());
                lista.push_back(novo_livro);           /// Adicionar o novo livro à lista existente
                cout << "\033[32mEste livro foi adicionado a colecao com sucesso!\033[0m" << endl;
                return;
            }
        }
    }if (existe == 0) {        /// Se não existir uma lista com um livro com esse nome, criar uma nova lista e adicionar a nova lista à biblioteca
        //cria link
        const string caracteresPermitidos = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        const int comprimentoLink = 10; // Comprimento do link desejado
        string linkGerado;
        srand(static_cast<unsigned int>(time(nullptr)));
        for (int i = 0; i < comprimentoLink; ++i) {
            int indice = rand() % caracteresPermitidos.length();
            linkGerado += caracteresPermitidos[indice];
        }
        string link = "https://www.sist.biblio.avac.com/pdf_livro/" + novo_livro->get_nome() + linkGerado;
        novo_livro->set_link(link);
    }
    list<Livro *> nova_lista;
    nova_lista.push_back(novo_livro);
    todos_livros.push_back(nova_lista);
    cout << "\033[32mEste livro foi adicionado ao acervo de livros da biblioteca com sucesso!\033[0m" << endl;
    auto compararNomeDoPrimeiroLivro = [](const std::list<Livro*>& lista1, const std::list<Livro*>& lista2) {        /// comparar o nome dos primeiros livros
        if (!lista1.empty() && !lista2.empty()) {
            return lista1.front()->get_nome() < lista2.front()->get_nome();
        }
        return false; // ou defina a lógica para lidar com listas vazias, se necessário
    };
    todos_livros.sort(compararNomeDoPrimeiroLivro);     /// Ordenar a lista de listas com base no comparador personalizado
}
void Biblioteca::criar_pedido_reserva(string matricula, Livro* l) {
    int total_livros;
    total_livros = get_usuario(matricula)->get_tamanho_emprestados() + get_usuario(matricula)->get_tamanho_reservados();
    if(get_usuario(matricula)->get_valor_multa() == 0 && total_livros < 3 && !get_usuario(matricula)->algum_livro_vencido()){   /// se o usuario nao estiver devendo e nem tiver livrovencido.
        if(verificar_existencia_pedido(matricula, l, pedidos_reserva)){    ///verifica se ja existe um pedido desse usuario para um exemplar desse livro.
            cout <<"\033[1;31mVoce ja possui um pedido de reserva deste livro!\033[0m" << endl;
            return;
        }
        PedidoReserva* pr = new PedidoReserva;
        pr->identificacao_usuario = matricula;
        pr->livro_pedido = l;
        pedidos_reserva.push_back(pr);
        ordenar_lista_pedidos("reservas");
        // Obtendo a data atual
        auto agora = chrono::system_clock::now();
        time_t data_atual = std::chrono::system_clock::to_time_t(agora);
        // Convertendo para struct tm para manipulação mais fácil
        tm* data_pedido_ptr = localtime(&data_atual);
        pr->data_pedido = *data_pedido_ptr; // atribui a data atual para data_pedido do pedido
        cout << "\033[32mPedido de reserva realizado com sucesso!\033[0m" << endl;
    }else if(get_usuario(matricula)->get_valor_multa() != 0){
        cout << "\033[1;31mVoce nao pode reservar livros pois esta devendo a biblioteca, pague a multa e tente novamente.\033[0m" << endl;
    }
    else if( total_livros >= 3){
        cout << "\033[1;31mVoce ja atingiu o numero maximo de livros (3), devolva um livro ou cancele uma reserva para poder pedir reserva de outro.\033[0m" << endl;
    }else if(get_usuario(matricula)->algum_livro_vencido()){
        cout << "\033[1;31mVoce nao pode reservar livros pois esta com um livro vencido, devolva ele e apos pagar a multa tente novamente.\033[0m" << endl;
    }
    return;
}
void Biblioteca::criar_pedido_renovar_emprestimo(string matricula, Livro *l) {
    if(verificar_existencia_pedido(matricula, l, pedidos_renovar_emprestimo)){
        cout <<"\033[1;31mVoce nao pode renovar emprestimo deste livro novamente!\033[0m" << endl;
        return;
    }else{
        PedidoReserva *pr = new PedidoReserva;
        pr->identificacao_usuario = matricula;
        pr->livro_pedido = l;
        // Obtendo a data atual
        auto agora = chrono::system_clock::now();
        time_t data_atual = std::chrono::system_clock::to_time_t(agora);
        // Convertendo para struct tm para manipulação mais fácil
        std::tm* data_pedido_ptr = std::localtime(&data_atual);
        // atribui a data atual para data_pedido do pedido
        pr->data_pedido = *data_pedido_ptr;
        pedidos_renovar_emprestimo.push_back(pr);
        ordenar_lista_pedidos("renovar emprestimo");
        cout << "\033[32mPedido de renovacao de reserva do livro " << l->get_nome() << " efetuado com sucesso!\033[0m" << endl;
        return;
    }
}
void Biblioteca::remover_livro(string id_livro) {
    for (auto it_lista = todos_livros.begin(); it_lista != todos_livros.end(); ++it_lista) {
        for (auto it_livro = it_lista->begin(); it_livro != it_lista->end(); ++it_livro) {
            if ((*it_livro)->get_id() == id_livro && (*it_livro)->get_estado_emprestimo() == "Disponivel") {
                // Remover o livro da lista
                it_lista->erase(it_livro);
                delete *it_livro;
                if(it_lista->empty()){
                    todos_livros.erase(it_lista);
                }
                cout << "\033[32mLivro foi removido com sucesso!\033[0m" << endl;
                return;
            }
        }
    }
    throw runtime_error("\033[1;31mLivro nao encontrado no acervo!\033[0m");
}
void Biblioteca::deletar_pedido_reserva(string identificaçao, string nome_livro) {
    for ( auto& pedido :pedidos_reserva){
        if(pedido->identificacao_usuario == identificaçao && pedido->livro_pedido->get_nome() == nome_livro){
            pedidos_reserva.remove(pedido);
            return;
        }
    }
}
void Biblioteca::deletar_pedido_renovar_emprestimo(string identificaçao, string nome_livro) {
    for ( auto& pedido :pedidos_renovar_emprestimo){
        if(pedido->identificacao_usuario == identificaçao && pedido->livro_pedido->get_nome() == nome_livro){
            pedidos_renovar_emprestimo.remove(pedido);
            return;
        }
    }
}
Usuario* Biblioteca::get_usuario(string identificacao) {
    for (const auto &usuario: usuarios) {
        if(usuario->get_identificacao() == identificacao){
            return usuario;
        }
    }
    return nullptr;
}
Funcionario* Biblioteca::get_funcionario(string identificacao){
    for (const auto &funcionario: funcionarios) {
        if(funcionario->get_identificacao() == identificacao){
            return funcionario;
        }
    }
    return nullptr;
}
void Biblioteca::ordenar_lista_pedidos(string lista) {  /// lista = a "reservas" oiu "renovar reservas"
    // Defina um comparador personalizado para a função sort
    auto comparador = [](const PedidoReserva* pr1, const PedidoReserva* pr2) {
        if (pr1->identificacao_usuario.size() != pr2->identificacao_usuario.size()) {           /// Comparação pelo tamanho da matrícula
            return pr1->identificacao_usuario.size() < pr2->identificacao_usuario.size();
        }
        return pr1->livro_pedido->get_nome() < pr2->livro_pedido->get_nome();   /// Comparação dos nomes dos livros
    };
    if(lista == "reservas") {
        // Ordena a lista de pedidos_reserva usando o comparador personalizado
        pedidos_reserva.sort(comparador);
    }
    if(lista == "renovar emprestimo") {
        // Ordena a lista de pedidos_reserva usando o comparador personalizado
        pedidos_renovar_emprestimo.sort(comparador);
    }
}
bool Biblioteca::verificar_existencia_pedido(string matricula, Livro* l, list<PedidoReserva*> lista_pedidos){
    for ( auto& pedido : lista_pedidos) {                      ///verifica se ja existe um pedido desse usuario para um exemplar desse livro.
        if(pedido->identificacao_usuario == matricula && pedido->livro_pedido->get_nome() == l->get_nome()){
            return true;
        }
    }
    return false;
}
void Biblioteca::ver_informacoes_livro() const {
    string id_livro;
    cout << "Insira a identificacao do livro que voce busca as informacoes: ";
    cin >> id_livro;
    if (id_livro.size() != 8 or !all_of(id_livro.begin(), id_livro.end(), [](char c) { return isdigit(c); })) {          // verifica se so tem numeros
        throw invalid_argument("\033[1;31mA identificacao deve conter 8 digitos e apenas numeros.\033[0m");
    }
    for (const auto& lista : todos_livros) {
        for (const auto& livro_ptr : lista) {
            if (livro_ptr->get_id() == id_livro) {
                livro_ptr->mostrar_informacoes();
                return;
            }
        }
    }
    throw runtime_error("\033[1;31mLivro nao encontrado!\033[0m");
}
Livro* Biblioteca::mostrar_exemplar_todos_livros() {
    system("cls");
    if(todos_livros.empty()){
        return nullptr;
    }
    vector<string> cabecalho_exemplares = {"Escolha um livro a seguir: "};
    vector<string> lista_disponiveis;
    for ( auto& lista : todos_livros) {
        int disponibilidade = verifica_disponiblidade_exemplar(lista.front()->get_nome());
        if (disponibilidade == 0) {
            string lista_info = lista.front()->get_nome() + ". | disponiveis: 0/"+ to_string(lista.size());;
            lista_disponiveis.push_back(lista_info);
        }else if (disponibilidade > 0) {
            string lista_info = lista.front()->get_nome() + ". | disponiveis: " + to_string(disponibilidade) + "/" + to_string(lista.size());
            lista_disponiveis.push_back(lista_info);
        }
    }
    string livro_escolhido = menu2(lista_disponiveis,cabecalho_exemplares);  /// este string guarda o nome da opçao escolhida.
    livro_escolhido = livro_escolhido.substr(0, livro_escolhido.find(".")); /// retorna apenas a parte do nome do livro contida na opcao escolhida.
    for (auto& lista : todos_livros) {          /// procura o livro com esse nome e retorna ele.
        for (auto& livro_ptr : lista) {
            if (livro_ptr->get_nome() == livro_escolhido && livro_ptr->get_estado_emprestimo() == "Disponivel") {
                return livro_ptr;
            }else if(livro_ptr->get_nome() == livro_escolhido && livro_ptr->get_estado_emprestimo() == "Reservado"){
                return livro_ptr;
            }else if (livro_ptr->get_nome() == livro_escolhido){
                return livro_ptr;
            }
        }
    }
    return nullptr;
}
PedidoReserva* Biblioteca::verificar_pedidos_reservas() {
    if(pedidos_reserva.empty()){
        return nullptr;
    }
    vector<PedidoReserva*> lista_pedidos_reserva;
    vector<int> quantidade;
    vector<string> cabecalho_pedidos_emprestimo = {"Lista de pedidos de emprestimo:"};
    for (const auto &pedido: pedidos_reserva) {               ///roda os pedidso de reserva
        lista_pedidos_reserva.push_back(pedido);                ///adiciona todos os pedidos de reserva a lista
        quantidade.push_back(verifica_disponiblidade_exemplar(pedido->livro_pedido->get_nome()));
    }
    PedidoReserva *pr = menu3(lista_pedidos_reserva, cabecalho_pedidos_emprestimo, quantidade);             ///a pessoa escolhe um pedido e retorna ele
    return pr;
}
PedidoReserva* Biblioteca::verificar_pedidos_renovar_emprestimo(){
    bool tem_pedido = false;
    for (const auto &pedido: pedidos_renovar_emprestimo){
        if(pedido->renovado == false){
            tem_pedido = true;
            break;
        }
    }
    if(pedidos_renovar_emprestimo.empty() or tem_pedido == false){
        return nullptr;
    }
    vector<PedidoReserva*> lista_pedidos_renovar_emprestimo;
    vector<int> quantidade;
    vector<string> cabecalho_renovar_emprestimo = {"Lista de pedidos para renovar emprestimo:"};
    for (const auto &pedido: pedidos_renovar_emprestimo) {               ///roda os pedidso de reserva
        if (pedido->renovado == false){
            lista_pedidos_renovar_emprestimo.push_back(pedido);                ///adiciona todos os pedidos de reserva a lista
            quantidade.push_back(verifica_disponiblidade_exemplar(pedido->livro_pedido->get_nome()));
        }
    }
    PedidoReserva *pr = menu3(lista_pedidos_renovar_emprestimo, cabecalho_renovar_emprestimo, quantidade);             ///a pessoa escolhe um pedido e retorna ele
    return pr;
}
void Biblioteca::dar_baixa_reserva_sistema(PedidoReserva *pr) {
    for ( auto& lista : todos_livros) {
        for ( auto& livro : lista) {
            if(pr->livro_pedido->get_nome() == livro->get_nome() && livro->get_estado_emprestimo() == "Disponivel"){
                for (const auto &usuario: usuarios) {                                 /// roda a lista de usuarios procurando o que tem matricula igual a do pedido.
                    if (usuario->get_identificacao() == pr->identificacao_usuario) {
                        livro->set_data_reserva(pr->data_pedido);
                        usuario->adicionar_livro_reservado(livro);
                        string msg = "Parabens, seu pedido de reserva do livro " + pr->livro_pedido->get_nome() +
                                     " foi aceito. Voce tem 72h para retira-lo.";
                        usuario->adicionar_aviso(msg);
                        livro->set_estado_emprestimo("Reservado");
                        if (verifica_disponiblidade_exemplar(pr->livro_pedido->get_nome()) == 0) {          ///se nao hoverem mais exemplares disponiveis.
                            ///enviar mensagem para os usuarios avisando que nao ha exemplares disponiveis e perguntar se permanecerao na lista de espera.
                            for (const auto &pedido: pedidos_reserva) {                     ///roda a lista de pedidos de reserva
                                int numero_espera = 0;
                                if (pr->livro_pedido->get_nome() == pedido->livro_pedido->get_nome()) {             ///se achar um pedido com o mesmo nome do do livro escolhido
                                    for (const auto &usuario2: usuarios) {                           ///roda os usuarios
                                        if (usuario2->get_identificacao() != pr->identificacao_usuario) {
                                            if (pedido->identificacao_usuario !=
                                                usuario2->get_identificacao()) {                   /// se o pedido tiver a matricula diferente da do usuario achado
                                                numero_espera++;                                                        /// ja que o livro tem o mesmo nome e o usuario é diferente adiciona 1
                                            }
                                            if (usuario2->get_identificacao() == pedido->identificacao_usuario) {
                                                string msg;

                                                if (numero_espera == 0) {
                                                    msg = "O Livro " + pr->livro_pedido->get_nome() +
                                                          " que voce pediu para reservar nao existe mais nenhum exemplar disponivel, voce e o proximo na lista de espera para este livro. Deseja permanecer na lista de espera?";
                                                } else {
                                                    msg = "O Livro " + pr->livro_pedido->get_nome() +
                                                          " que voce pediu para reservar nao existe mais nenhum exemplar disponivel, ha " +
                                                          to_string(numero_espera ) +
                                                          " pedidos na sua frente. Deseja permanecer na lista de espera?";
                                                }
                                                usuario2->adicionar_aviso(msg);
                                                break;
                                            }
                                        }
                                    }

                                }
                            }
                        }
                        for (const auto &pedido: pedidos_reserva) {
                            if (pedido->livro_pedido->get_nome() == pr->livro_pedido->get_nome() && pedido->identificacao_usuario == pr->identificacao_usuario) {        //&& pedido->info_tempo_pedido == pr->info_tempo_pedido
                                pedidos_reserva.remove(pedido);
                                return;
                            }
                        }
                    }
                }
            }else if(pr->livro_pedido->get_nome() == livro->get_nome() && livro->get_estado_emprestimo() != "Disponivel"){ /// essalinha é umteste.
                throw runtime_error("\033[1;31mNao foi possivel reservar, este livro nao esta disponivel!\033[0m");
            }
        }
    }
}
void Biblioteca::dar_baixa_renovar_emprestimo_sistema(PedidoReserva *pr) {
    /// Deve mudar a data de entrega do livro que esta emprestado a esse usuario.
    for (const auto &usuario: usuarios) {
        if(usuario->get_identificacao() == pr->identificacao_usuario){
            string msg = "Parabens, seu pedido de renovar reserva do livro " + pr->livro_pedido->get_nome() + " foi aceito!";
            usuario->adicionar_aviso(msg);
            pr->livro_pedido->prolonga_data_devolucao();
        }
    }
}
bool Biblioteca::pedido_renovar_emprestimo_efetuado(string nome_pedido, string matricula) {
    for ( auto& pedido : pedidos_renovar_emprestimo) {
        if(pedido->livro_pedido->get_nome() == nome_pedido && pedido->identificacao_usuario == matricula){
            if( pedido->renovado == false){
                return false;

            }if( pedido->renovado == true) {
                return true;
            }
        }
    }
}
int Biblioteca::verifica_disponiblidade_exemplar(string nome_livro) {
    int livros_disponiveis = 0;
    for ( auto& lista : todos_livros) {
        if(lista.front()->get_nome() == nome_livro){
            for (auto &livro_ptr: lista) {
                if (livro_ptr->get_estado_emprestimo() == "Disponivel") {
                    livros_disponiveis++;
                }
            }
            return livros_disponiveis;
        }
    }
    throw runtime_error("\033[1;31mNao ha livros com esse nome\033[0m");
}
void Biblioteca::atualizar_geral() {
    for (const auto &usuario: usuarios) {
        usuario->atualizar();
    }
    for (const auto &pedido: pedidos_renovar_emprestimo) { ///atualiza a lista de renovar reserva, retirando os pedidos de mais de 3 dias
        chrono::system_clock::time_point now = chrono::system_clock::now();        // Obtendo a data atual
        time_t data_atual = chrono::system_clock::to_time_t(now);
        tm *data_atual_tm = localtime(&data_atual);
        // Convertendo ambas as datas para time_t para cálculos
        time_t time1 = mktime(&pedido->data_pedido);
        time_t time2 = mktime(data_atual_tm);
        // Calculando a diferença em segundos
        chrono::seconds diff = chrono::seconds(time2 - time1);
        // Convertendo a diferença para dias
        int dias = chrono::duration_cast<chrono::hours>(diff).count() / 24;
        if (dias > 3 && pedido->renovado == 0) {
            pedido->data_pedido = {};
            string aviso = "Seu pedido para renovar o livro " + pedido->livro_pedido->get_nome() + " expirou!";
            get_usuario(pedido->identificacao_usuario)->adicionar_aviso(aviso);
            pedidos_renovar_emprestimo.remove(pedido);
            return;
        }
    }
}
bool Biblioteca::verificar_existencia_livro(string id_livro) {
    for (const auto& lista : todos_livros) {
        for (const auto& livro_ptr : lista) {
            if (livro_ptr->get_id() == id_livro){
                return true;
            }
        }
    }
    return false;
}

