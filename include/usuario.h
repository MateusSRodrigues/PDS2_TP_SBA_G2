#ifndef USUARIO_H
#define USUARIO_H

#include "pessoa.h"
#include "biblioteca.h"
#include <vector>
#include <string>
#include <list>

class Biblioteca;

class Usuario : public Pessoa{
private:
    float valor_multa = 0;
    list <Livro*> livros_em_uso;
    list <Livro*> livros_reservados;
    list <string> avisos;

public:
    Usuario(string n, string sen, string t, string id);
    void mostrar_informacoes_de_cadastro() override;
    float get_valor_multa();
    void pagar_multa();
    int get_tamanho_reservados();
    int get_tamanho_emprestados();
    void ver_livros_emprestados(); /// temporario para testes
    void ver_livros_reservados();   ///temporario para testes
    void adicionar_aviso(string msg);
    void ler_avisos(Biblioteca* b);
    void adicionar_livro_reservado(Livro *l);
    string mostrar_livros_reservados(string acao); //apaga o livro de reservas e manda para livros_em_uso- a string é para caso cancele a reserva ou caso retire o livro
    string mostrar_livros_em_uso(string acao);    //apaga o livro de reservas e manda para livros_em_uso - a string é para caso devolva o livro ou renove emprestimo
    bool algum_livro_vencido();
    void reservar_livro(Biblioteca* b);
    void cancelar_reserva();
    void retirar_livro();
    void retirar_livro_online(Biblioteca* b1);
    void devolver_livro(Biblioteca* b1);
    void renovar_emprestimo(Biblioteca* b1);
    void atualizar();
};

#endif //ENTREGA_FINAL_USUARIO_H
