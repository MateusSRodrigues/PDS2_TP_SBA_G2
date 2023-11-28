//
// Created by rayda on 31/10/2023.
//

#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H
#include "Livro.h"
#include "Usuario.h"
#include "Funcionario.h"
#include "PedidoReserva.h"
#include <list>
#include<vector>
//oi
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
    void criar_usuario(string n, string sen, string t, string id);
    void criar_funcionario(string n, string sen, string t, string id, string turno);
    void adicionar_livro(Livro* novo_livro );
    void criar_pedido_reserva(string matricula, Livro *l);
    void criar_pedido_renovar_emprestimo(string matricula, Livro *l);
    void remover_livro(string id_livro);
    void deletar_pedido_reserva(string identificaçao, string nome_livro);
    void deletar_pedido_renovar_emprestimo(string identificaçao, string nome_livro);
    Usuario* get_usuario(string identificacao);
    Funcionario* get_funcionario(string identificacao);
    void ordenar_lista_pedidos(string lista); // ordena a lista de reserva ou a de renovar reserva depedendo da string lista
    static bool verificar_existencia_pedido(string matricula, Livro* l, list<PedidoReserva*> lista_pedidos);
    void ver_informacoes_livro() const;
    Livro* mostrar_exemplar_todos_livros();
    PedidoReserva* verificar_pedidos_reservas();// escolhe o pedido da lista de reserva ou a de renovar reserva depedendo da string lista
    PedidoReserva* verificar_pedidos_renovar_emprestimo();
    void dar_baixa_reserva_sistema(PedidoReserva *pr);
    void dar_baixa_renovar_emprestimo_sistema(PedidoReserva *pr);
    bool pedido_renovar_emprestimo_efetuado(string nome_pedido, string matricula);
    int verifica_disponiblidade_exemplar(string nome_livro);
    void atualizar_geral();
    bool verificar_existencia_livro(string id_livro);
};

#endif //ENTREGA1_BIBLIOTECA_H
