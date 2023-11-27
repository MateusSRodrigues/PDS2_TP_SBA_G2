//
// Created by rayda on 31/10/2023.
//
#include <string>
#include <iostream>

#ifndef LIVRO_H
#define LIVRO_H

using namespace std;
class Livro {
private:
    string nome_livro;
    string autor;
    string numero_id;
    string estado_fisico;
    int ano_publicacao;
    int avaliacao;
    int quantidade_livros;

public:
   //void diminuir_quantidade();
   //void aumentar_quantidade();

   //recebe um inteiro como avaliaçao do aluno e ja calcula a media e altera a a variavel "avaliacao"
   void receber_avaliacao(int valor);





};


#endif //SISTEMA_BIBLIOTECA_AVANÇADA_LIVRO_H
