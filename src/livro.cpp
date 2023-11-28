//
// Created by rayda on 02/11/2023.
//

#include "livro.h"

Livro::Livro(string nome, string autor, string id, string ef, string ano) : nome_livro(nome),autor(autor),  numero_id(id), estado_fisico(ef), ano_publicacao(ano), avaliacao(10), estado_emprestimo("Disponivel"){

}
string Livro::get_nome() {
    return nome_livro;
}
string Livro::get_autor() {
    return autor;
}
string Livro::get_id() {
    return numero_id;
}
string Livro::get_estado_fisico() {
    return estado_fisico;
}
string Livro::get_ano_publicacao() {
    return ano_publicacao;
}
string Livro::get_estado_emprestimo() {
    return estado_emprestimo;
}
string Livro::get_link() {
    return link;
}
int Livro::get_avaliacao() {
    return avaliacao;
}
tm* Livro::get_data_vencimento() {
    return &data_vencimento;
}
tm *Livro::get_data_reserva() {
    return &data_reserva;
}
void Livro::set_estado_fisico(string novo_estado) {
    estado_fisico = novo_estado;
}
void Livro::set_estado_emprestimo(string novo_estado) {
    if(novo_estado != "Disponivel" && novo_estado != "Reservado" && novo_estado != "Emprestado"){
        throw invalid_argument ("\033[1;31mNovo estado do livro e invalido.\033[0m");
    }
    estado_emprestimo = novo_estado;
}
void Livro::set_data_reserva(tm data) {
    data_reserva = data;
}
void Livro::set_link(string novo_link) {
    link = novo_link;
}
void Livro::mostrar_informacoes() {
    system("cls");
    cout << "###############################################" << endl << "\033[0;35mInformacoes do livro.\033[0m" << endl << "-------------------------------------" << endl;
    cout << "\033[0;35mNome : \033[0m \033[32m" << nome_livro << ".\033[0m" << endl << "\033[0;35mAutor: \033[0m \033[32m" << autor << ".\033[0m" << endl << "\033[0;35mAno de publicacao: \033[0m \033[32m";
    cout << ano_publicacao << ".\033[0m" << endl << "\033[0;35mAvaliacao: \033[0m \033[32m" << avaliacao << "/10.\033[0m" << endl << "\033[0;35mEstado fisico: \033[0m \033[32m" << estado_fisico << ".\033[0m" << endl;
    cout << "\033[0;35mEstado de emprestimo: \033[0m \033[32m" << estado_emprestimo << ".\033[0m"<< endl << "\033[0;35mLink: \033[0m" << link << endl;
    if (estado_emprestimo == "Reservado"){
        cout << "\033[0;35mData de reserva: \033[32m" << data_reserva.tm_mday << "/" << data_reserva.tm_mon + 1 << "/" << data_reserva.tm_year << ".\033[0m" << endl;
    } else if (estado_emprestimo == "Emprestado"){
        cout << "\033[0;35mData de emprestimo: \033[0m \033[32m" << data_emprestimo.tm_mday << "/" << data_emprestimo.tm_mon + 1 << "/" << data_emprestimo.tm_year << ".\033[0m" << endl;
        cout << "\033[0;35mDevolucao prevista: \033[0m \033[32m" << data_vencimento.tm_mday << "/" << data_vencimento.tm_mon + 1 << "/" << data_vencimento.tm_year << ".\033[0m" << endl;
    }
    cout << "###############################################" << endl << "###############################################";
}
void Livro::receber_avaliacao(int valor) {
    numero_avaliacoes++;
    avaliacao = ((numero_avaliacoes * avaliacao) + valor)/ numero_avaliacoes;
}
void Livro::atribui_data_emprestimo() {
    // Obtendo a data atual
    auto agora = chrono::system_clock::now();
    time_t data_atual = std::chrono::system_clock::to_time_t(agora);
    // Convertendo para struct tm para manipulação mais fácil
    std::tm* data_emprestimo_ptr = std::localtime(&data_atual);
    data_emprestimo = *data_emprestimo_ptr; // atribui a data atual para data_emprestimo
    // Incrementando o mês para o próximo mês
    data_emprestimo.tm_mon += 1;
    // Convertendo para segundos para permitir manipulação de tempo
    std::time_t data_proximo_mes = std::mktime(&data_emprestimo);
    // Convertendo de volta para struct tm para data_vencimento
    std::tm* data_vencimento_ptr = std::localtime(&data_proximo_mes);
    data_vencimento = *data_vencimento_ptr; // atribui a data de vencimento para o próximo mês
}
void Livro::zerar_datas_livro() {
    data_vencimento = {};
    data_emprestimo = {};
    data_reserva = {};
}
void Livro::prolonga_data_devolucao() {
// Convertendo data_vencimento para time_t para cálculos
    time_t time_vencimento = std::mktime(&data_vencimento);
    // Adicionando 30 dias em segundos
    chrono::seconds trinta_dias(30 * 24 * 60 * 60);
    // Convertendo para chrono::system_clock::time_point para operações
    chrono::system_clock::time_point vencimento_point = chrono::system_clock::from_time_t(time_vencimento);
    vencimento_point += trinta_dias;
    // Convertendo de volta para time_t
    time_t novo_vencimento = chrono::system_clock::to_time_t(vencimento_point);
    // Atualizando data_vencimento com o novo valor
    data_vencimento = *localtime(&novo_vencimento);
}
Livro::~Livro() {
    ///cout << "livro " << nome_livro << " destruido!!" << endl;
}






