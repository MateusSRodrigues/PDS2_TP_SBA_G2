//
// Created by rayda on 31/10/2023.
//

#ifndef ENTREGA1_BIBLIOTECA_H
#define ENTREGA1_BIBLIOTECA_H
#include "Livro.h"
#include "Usuario.h"
#include "Funcionario.h"
#include <list>
#include<vector>

class Usuario;
class Funcionario;

string menu2(vector<string>& opcao,  vector<string>& cabecalho);
PedidoReserva* menu3(vector<PedidoReserva*>& opcao,  vector<string>& cabecalho);

class Biblioteca {
private:
    list<PedidoReserva*> pedidos_reserva;
    list<PedidoReserva*> pedidos_renovar_emprestimo;
    list<Usuario*> usuarios;
    list<list<Livro*>> todos_livros;
    list<Funcionario*> funcionarios;

public:
    bool pedido_renovar_emprestimo_efetuado(string nome_pedido, string matricula);
     void criar_usuario(string n, string sen, string t, string id);
    void criar_funcionario(string n, string sen, string t, string id, string turno);
    void adicionar_livro(Livro* novo_livro );
    void criar_pedido_reserva(string matricula, Livro *l);
    void criar_pedido_renovar_emprestimo(string matricula, Livro *l);
    void remover_livro(string id_livro);
    void deletar_pedido_reserva(string identificaçao, string nome_livro);
    void deletar_pedido_renovar_emprestimo(string identificaçao, string nome_livro);
    Usuario* get_usuario(string identificacao);
};


#endif //ENTREGA1_BIBLIOTECA_H
