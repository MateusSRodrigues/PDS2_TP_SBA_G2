//
// Created by rayda on 02/11/2023.
//

#include <unistd.h>
#include <algorithm>
#include "funcionario.h"

Funcionario::Funcionario(string n, string sen, string t, string id, string turno) : Pessoa(n, sen, t, id) ,turno_trabalho(turno) {
}
void Funcionario::mostrar_informacoes_de_cadastro() {
    cout << "###############################################" << endl;
    cout << "\033[0;35mSuas informacoes.\033[0m" << endl;
    cout << "------------------------" << endl;
    cout << "\033[0;35mNome: \033[0m\033[32m" << get_nome() << ".\033[0m" << endl;
    cout << "\033[0;35mIdentificacao: \033[0m\033[32m" << get_identificacao() << ".\033[0m" << endl;
    cout << "\033[0;35mTelefone: \033[0m\033[32m" << get_telefone() << ".\033[0m" << endl;
    cout << "\033[0;35mTurno de trabalho: \033[0m\033[32m" << turno_trabalho << ".\033[0m" << endl;
    cout << "###############################################" << endl;
}
void Funcionario::mostrar_informacoes_de_cadastro(Biblioteca *b1) {
    string identificacao;
    cout << "Insira a identificacao do usuario a ser buscado: ";
    cin >> identificacao;
    if (identificacao.size() != 7 && identificacao.size() != 9) {              /////////////////////////////////////////////////////////
        throw invalid_argument("\033[1;31mO ID deve ter 7 ou 9 digitos.\033[0m");
    }
    if (!all_of(identificacao.begin(), identificacao.end(), [](char c) { return isdigit(c); })) {          // verifica se so tem numeros
        throw invalid_argument("\033[1;31mA identificacao deve conter apenas numeros.\033[0m");
    }
    if (b1->get_usuario(identificacao) == nullptr) {            // Verifica se o ID já existe na lista de usuários
        throw invalid_argument("\033[1;31mEsta Identificacao nao existe.\033[0m");
    }                                                                                                       /////////////////////////////////////////////////////////////
    b1->get_usuario(identificacao)->mostrar_informacoes_de_cadastro();
}
void Funcionario::cadastrar_livro(Biblioteca* b1) {
    string nome, autor, ident, estado_fisico, ano;
    //int num_ef;
    cout << "Nome: ";
    cin >> nome;
    cout << "Autor:";
    cin >> autor;
    cout << "Id: ";
    cin >> ident;
    cout << "Estado fisico [1(Pessimo), 2(Ruim), 3(Medio), 4(Bom), 5(Otimo)]: ";
    cin >> estado_fisico;
    cout << "Ano publicacao: ";
    cin >> ano;
    if (any_of(autor.begin(), autor.end(), [](char c) {return !isalpha(c) && !isspace(c);})) {            // Verifica se o nome contém apenas letras
        throw invalid_argument("\033[1;31mO nome do autor deve conter apenas letras.\033[0m");
    }
    if (b1->verificar_existencia_livro(ident)) {
        throw invalid_argument("\033[1;31mJa existe um livro com essa identificacao.\033[0m");
    }
    if (ident.size() != 8) {
        throw invalid_argument("\033[1;31mID invalido, insira um valor de 8 digitos.\033[0m");
    }
    if (!all_of(ident.begin(), ident.end(), [](char c) {
        return isalnum(c);
    })) {
        throw invalid_argument("\033[1;31mA Identificacao deve ter apenas caracteres alfanumericos.\033[0m");
    }
    if (estado_fisico != "1" && estado_fisico != "2" && estado_fisico != "3" &&
        estado_fisico != "4" && estado_fisico != "5") {
        throw invalid_argument("\033[1;31mEstado fisico invalido insira um numero de 1 a 5.\033[0m");
    }

    if (!all_of(ano.begin(), ano.end(), [](char c) { return isalnum(c); })) {
        throw invalid_argument("\033[1;31mAno invalido, digite apenas numeros.\033[0m");
    }
    if(estado_fisico == "1"){estado_fisico = "Pessimo";}
    else if(estado_fisico == "2") {estado_fisico = "Ruim";}
    else if(estado_fisico == "3") {estado_fisico = "Medio";}
    else if(estado_fisico == "4") {estado_fisico = "Bom";}
    else if(estado_fisico == "5") {estado_fisico = "Otimo";}
    Livro* l = new Livro(nome, autor, ident, estado_fisico, ano);
    b1->adicionar_livro(l);
}
void Funcionario::descadastrar_livro(Biblioteca* b1) {
    string ident;
    cout<< "insira a identificacao do livro que deseja descadastrar: ";
    cin >> ident;
    if (ident.size() != 8 or !all_of(ident.begin(), ident.end(), [](char c) { return isdigit(c); })) {          // verifica se so tem numeros
        throw invalid_argument("\033[1;31mA identificacao deve conter 8 digitos e apenas numeros.\033[0m");
    }                                                                                                                                                /////////////////
    b1->remover_livro(ident);
}
void Funcionario::dar_baixa_reserva(PedidoReserva *pr, Biblioteca* b1) {
    if(pr == nullptr){                                                                                      ///////////////////////////
        throw runtime_error ("\033[1;31mNao ha pedidos de reserva!\033[0m");
    }else {                                                                                                       /////////////////////////
        vector<string> opcao = {"Sim", "Nao"};
        vector<string> cabecalho_liberar = {"Deseja liberar reserva?"};
        if (menu2(opcao, cabecalho_liberar) == "Sim") {
            b1->dar_baixa_reserva_sistema(pr);
            cout << "\033[32mPedido de reserva aceito!\033[0m" << endl;

        } else {
            b1->get_usuario(pr->identificacao_usuario)->adicionar_aviso(
                    "Seu pedido de reserva foi negado."); /// envia uma mensagem para o usuario.
            cout << "voce negou o pedido do usuario " << pr->identificacao_usuario << "!" << endl;
            b1->deletar_pedido_reserva(pr->identificacao_usuario, pr->livro_pedido->get_nome());
        }
        return;
    }
}
void Funcionario::dar_baixa_renovar_emprestimo(PedidoReserva *pr, Biblioteca *b1) {
    if (pr == nullptr) {                                                                                        //////////////
        throw runtime_error ("\033[1;31mNao ha pedidos de renovar emprestimo!\033[0m");
    }                                                                                                           /////////////
    vector<string> opcao = {"Sim", "Nao"};
    vector<string> cabecalho_renovar = {"Deseja liberar renovacao de emprestimo?"};
    if (menu2(opcao, cabecalho_renovar) == "Sim") {
        b1->dar_baixa_renovar_emprestimo_sistema(pr);
        pr->renovado = true;
    } else {
        b1->get_usuario(pr->identificacao_usuario)->adicionar_aviso(
                "Seu pedido de renovar emprestimo foi negado!"); /// envia uma mensagem para o usuario.
        b1->deletar_pedido_renovar_emprestimo(pr->identificacao_usuario, pr->livro_pedido->get_nome());
    }
}
void Funcionario::entregar_livro_presencialmente(Biblioteca* b1) {
    string id;
    cout << "Insira a identificacao do usuario que deseja retirar o livro: ";
    cin >> id; /// tratamento de excessao para n usar espacos e nem letras.
    if(b1->get_usuario(id) == nullptr){
        throw runtime_error ("\033[1;31mNao existe usuario com esta identificacao!\033[0m");
    }else { ///se existir.
        b1->get_usuario(id)->retirar_livro();
    }
}
void Funcionario::aceitar_devolucao_livro_presencialmente(Biblioteca *b1) {
    string id;
    cout << "Insira a identificacao do usuario que deseja devolver o livro: ";
    cin >> id;
    if(b1->get_usuario(id) == nullptr){
        throw runtime_error ("\033[1;31mNao existe usuario com esta identificacao!\033[0m");
    }else{ ///se existir.
        b1->get_usuario(id)->devolver_livro(b1);

    }
}
///-----------------------------------------------------------------------


