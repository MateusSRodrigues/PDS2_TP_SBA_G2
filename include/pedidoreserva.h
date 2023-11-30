#ifndef PEDIDORESERVA_H
#define PEDIDORESERVA_H


#include <algorithm>
#include "livro.h"

using  namespace std;
class PedidoReserva {
public:
    string identificacao_usuario;
    Livro *livro_pedido;
    bool renovado = false;
    tm data_pedido;
};


#endif //PROJETOBIBLIOTECA_PEDIDORESERVA_H
