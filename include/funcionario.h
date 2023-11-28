#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

#include "PedidoReserva.h"
#include "Biblioteca.h"
#include "Pessoa.h"
#include "Usuario.h"
#include <ctime>

class Biblioteca;
class Usuario;
class Funcionario: public Pessoa {

private:
    string turno_trabalho;
public:
//    void adicionar_na_lista_pedidos_reserva(PedidoReserva* pr);
    Funcionario(string n, string sen, string t, string id, string turno);
    void mostrar_informacoes_de_cadastro() override;
    void mostrar_informacoes_de_cadastro(Biblioteca* b1);
    void cadastrar_livro(Biblioteca* b1);
    void descadastrar_livro(Biblioteca* b1);
    void dar_baixa_reserva(PedidoReserva* pr,Biblioteca* b1);
    void dar_baixa_renovar_emprestimo(PedidoReserva* pr,Biblioteca* b1);
    void entregar_livro_presencialmente(Biblioteca* b1);
    void aceitar_devolucao_livro_presencialmente(Biblioteca* b1);
    void registrar_condicao_livro(Livro l); ///deveria ficar aqui, mas ta no devover do usuario

};


#endif //ENTREGA1_FUNCIONARIO_H
