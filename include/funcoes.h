#ifndef FUNCOES_H
#define FUNCOES_H

#include <string>
#include <vector>

#include "biblioteca.h"
#include "pedidoreserva.h"

using namespace std;

//class Biblioteca;

string menu2(vector<string>& opcao,  vector<string>& cabecalho);
PedidoReserva* menu3(vector<PedidoReserva*>& opcao,  vector<string>& cabecalho, vector<int>& quant);
void cadastrar(Biblioteca* b);



#endif