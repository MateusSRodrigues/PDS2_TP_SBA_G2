#ifndef LIVRO_H
#define LIVRO_H
#include <string>
#include <iostream>
#include <list>
#include <chrono>
#include <ctime>

using namespace std;
class Livro {
private:
    string nome_livro;
    string autor;
    string numero_id;
    string estado_fisico;
    string ano_publicacao;
    string estado_emprestimo;
    string link;
    int numero_avaliacoes;
    int avaliacao;
    tm data_reserva;
    tm data_emprestimo;
    tm data_vencimento;

public:
    Livro(string nome, string autor, string id, string ef, string ano);
    string get_nome();
    string get_autor();
    string get_id();
    string get_estado_fisico();
    string get_ano_publicacao();
    string get_estado_emprestimo();
    string get_link();
    int get_avaliacao();
    tm* get_data_vencimento();
    tm* get_data_reserva();
    void set_link(string novo_link);
    void set_data_reserva(tm data);
    void set_estado_fisico(string novo_estado);
    void set_estado_emprestimo(string novo_estado);
    void mostrar_informacoes();
    void receber_avaliacao(int valor);
    void atribui_data_emprestimo();
    void prolonga_data_devolucao();
    void zerar_datas_livro();

    ~Livro();
};


#endif //ENTREGA_FINAL_LIVRO_H
