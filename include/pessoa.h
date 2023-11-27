//
// Created by rayda on 31/10/2023.
//
#include <string>
#include <iostream>
#include "Livro.h"

#ifndef PESSOA_H
#define PESSOA_H

using namespace std;

class Pessoa {
private:
    string nome;
    string senha;
    string telefone;
    string identificacao;

public:
    Pessoa(string n, string sen, string t, string id);
    string get_nome();
    string get_telefone();
    string get_identificacao();
    string get_senha();
    virtual void mostrar_informacoes_de_cadastro() = 0;
    void avaliar_livro(Livro l);
};


#endif //ENTREGA1_PESSOA_H