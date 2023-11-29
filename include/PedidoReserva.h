#ifndef PROJETOBIBLIOTECA_PEDIDORESERVA_H
#define PROJETOBIBLIOTECA_PEDIDORESERVA_H


#include <algorithm>
#include "Livro.h"

using  namespace std;
class PedidoReserva {
public:
    string identificacao_usuario;
    Livro *livro_pedido;
    bool renovado = false;
    tm data_pedido;
};


#endif //PROJETOBIBLIOTECA_PEDIDORESERVA_H
