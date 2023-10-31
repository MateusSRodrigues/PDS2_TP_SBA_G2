//
// Created by rayda on 31/10/2023.
//


#ifndef ENTREGA1_USUARIO_H
#define ENTREGA1_USUARIO_H


#include <list>
#include "Pessoa.h"

class Usuario : public Pessoa{
private:
    list <Livro> livros_em_uso;
public:
    void reservar_livro(list <Livro> livros, list <string> reservas);   ///apaga o livro de livros e manda para reservas
    void cancelar_reserva(list <string> reservas,list <Livro> livros);
    void ver_multas();
    void retirar_livro(Livro l,list <string> reservas);     ///apaga o livro de reservas e manda para livros_em_uso

};


#endif //ENTREGA1_USUARIO_H
