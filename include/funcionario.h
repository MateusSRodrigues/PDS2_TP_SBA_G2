//
// Created by rayda on 31/10/2023.
//

#ifndef ENTREGA1_FUNCIONARIO_H
#define ENTREGA1_FUNCIONARIO_H


#include "Pessoa.h"
#include "Usuario.hpp"

class Funcionario: public Pessoa {
private:

public:
    void informacoes_de_cadastro(Usuario u);
    void ver_multa(Usuario u);
    void pagar_multa(Usuario u, list<string> multas);
    void entregar_livro_presencialmente(Livro l, Usuario u);
    void cadastro_livro_novo(list<Livro> livros);
    void registrar_condicao_livro(Livro l);
    void renovar_emprestimo();
};


#endif //ENTREGA1_FUNCIONARIO_H
