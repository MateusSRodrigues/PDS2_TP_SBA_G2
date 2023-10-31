//
// Created by rayda on 31/10/2023.
//
#include <string>
#include <iostream>
#include "Livro.h"

#ifndef ENTREGA1_PESSOA_H
#define ENTREGA1_PESSOA_H

using namespace std;

class Pessoa {
private:
    string nome;
    string senha;
    string telefone;
    string identificacao;

public:
    void avaliar_livro(Livro l);
    void informacoes_de_cadastro();

};


#endif //ENTREGA1_PESSOA_H
