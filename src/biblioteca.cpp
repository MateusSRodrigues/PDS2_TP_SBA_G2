///
//
// Created by rayda on 02/11/2023.

#include <vector>
#include <unistd.h>
#include <conio.h>
#include "Biblioteca.h"

void Biblioteca::criar_usuario(string n, string sen, string t, string id) {
    Usuario *user = new Usuario(n,sen,t,id);
    usuarios.push_back(user);
}
void Biblioteca::criar_funcionario(string n, string sen, string t, string id, string turno) {
    Funcionario *func = new Funcionario(n,sen,t,id,turno);
    funcionarios.push_back(func);
}
void Biblioteca::adicionar_livro(Livro* novo_livro) {
    bool existe = 0 ;    /// Verificar se já existe uma lista com um livro com este nome
    for (auto& lista : todos_livros) {
        for (auto& livro_ptr : lista) {
            if (lista.front()->get_nome() == novo_livro->get_nome()) {   ///se ja existir um livro com esse nome, o livro criado é adicionado ao list dele.
                existe = 1;
                novo_livro->set_link(lista.front()->get_link());
                lista.push_back(novo_livro);           /// Adicionar o novo livro à lista existente
                cout << "\033[32mEste livro foi adicionado a colecao com sucesso!\033[0m" << endl;
                return;
            }
        }
    }if (existe == 0) {        /// Se não existir uma lista com um livro com esse nome, criar uma nova lista e adicionar a nova lista à biblioteca
        //cria link
        const string caracteresPermitidos = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        const int comprimentoLink = 10; // Comprimento do link desejado
        string linkGerado;
        srand(static_cast<unsigned int>(time(nullptr)));
        for (int i = 0; i < comprimentoLink; ++i) {
            int indice = rand() % caracteresPermitidos.length();
            linkGerado += caracteresPermitidos[indice];
        }
        string link = "https://www.sist.biblio.avac.com/pdf_livro/" + novo_livro->get_nome() + linkGerado;
        novo_livro->set_link(link);
    }
    list<Livro *> nova_lista;
    nova_lista.push_back(novo_livro);
    todos_livros.push_back(nova_lista);
    cout << "\033[32mEste livro foi adicionado ao acervo de livros da biblioteca com sucesso!\033[0m" << endl;
    auto compararNomeDoPrimeiroLivro = [](const std::list<Livro*>& lista1, const std::list<Livro*>& lista2) {        /// comparar o nome dos primeiros livros
        if (!lista1.empty() && !lista2.empty()) {
            return lista1.front()->get_nome() < lista2.front()->get_nome();
        }
        return false; // ou defina a lógica para lidar com listas vazias, se necessário
    };
    todos_livros.sort(compararNomeDoPrimeiroLivro);     /// Ordenar a lista de listas com base no comparador personalizado
}
void Biblioteca::criar_pedido_reserva(string matricula, Livro* l) {
    int total_livros;
    total_livros = get_usuario(matricula)->get_tamanho_emprestados() + get_usuario(matricula)->get_tamanho_reservados();
    if(get_usuario(matricula)->get_valor_multa() == 0 && total_livros < 3 && !get_usuario(matricula)->algum_livro_vencido()){   /// se o usuario nao estiver devendo e nem tiver livrovencido.
        if(verificar_existencia_pedido(matricula, l, pedidos_reserva)){    ///verifica se ja existe um pedido desse usuario para um exemplar desse livro.
            cout <<"\033[1;31mVoce ja possui um pedido de reserva deste livro!\033[0m";
            return;
        }
        PedidoReserva* pr = new PedidoReserva;
        pr->identificacao_usuario = matricula;
        pr->livro_pedido = l;
        pedidos_reserva.push_back(pr);
        ordenar_lista_pedidos("reservas");
        // Obtendo a data atual
        auto agora = chrono::system_clock::now();
        time_t data_atual = std::chrono::system_clock::to_time_t(agora);
        // Convertendo para struct tm para manipulação mais fácil
        std::tm* data_pedido_ptr = std::localtime(&data_atual);
        pr->data_pedido = *data_pedido_ptr; // atribui a data atual para data_pedido do pedido
        cout << "\033[32mPedido de reserva realizado com sucesso!\033[0m" << endl;
    }else if(get_usuario(matricula)->get_valor_multa() != 0){
        cout << "\033[1;31mVoce nao pode reservar livros pois esta devendo a biblioteca, pague a multa e tente novamente.\033[0m" << endl;
    }
    else if( total_livros >= 3){
        cout << "\033[1;31mVoce ja atingiu o numero maximo de livros (3), devolva um livro ou cancele uma reserva para poder pedir reserva de outro.\033[0m" << endl;
    }else if(get_usuario(matricula)->algum_livro_vencido()){
        cout << "\033[1;31mVoce nao pode reservar livros pois esta com um livro vencido, devolva ele e apos pagar a multa tente novamente.\033[0m" << endl;
    }
    return;
}
void Biblioteca::criar_pedido_renovar_emprestimo(string matricula, Livro *l) {
    if(verificar_existencia_pedido(matricula, l, pedidos_renovar_emprestimo)){
        cout <<"\033[1;31mVoce nao pode renovar emprestimo deste livro novamente!\033[0m";
        return;
    }else{
        PedidoReserva *pr = new PedidoReserva;
        pr->identificacao_usuario = matricula;
        pr->livro_pedido = l;
        // Obtendo a data atual
        auto agora = chrono::system_clock::now();
        time_t data_atual = std::chrono::system_clock::to_time_t(agora);
        // Convertendo para struct tm para manipulação mais fácil
        std::tm* data_pedido_ptr = std::localtime(&data_atual);
        // atribui a data atual para data_pedido do pedido
        pr->data_pedido = *data_pedido_ptr;
        pedidos_renovar_emprestimo.push_back(pr);
        ordenar_lista_pedidos("renovar emprestimo");
        cout << "\033[32mPedido de renovacao de reserva do livro " << l->get_nome() << " efetuado com sucesso!\033[0m" << endl;
        return;
    }
}
void Biblioteca::remover_livro(string id_livro) {
    for (auto it_lista = todos_livros.begin(); it_lista != todos_livros.end(); ++it_lista) {
        for (auto it_livro = it_lista->begin(); it_livro != it_lista->end(); ++it_livro) {
            if ((*it_livro)->get_id() == id_livro && (*it_livro)->get_estado_emprestimo() == "Disponivel") {
                // Remover o livro da lista
                it_lista->erase(it_livro);
                delete *it_livro;
                if(it_lista->empty()){
                    todos_livros.erase(it_lista);
                }
                cout << "\033[32mLivro foi removido com sucesso!\033[0m" << endl;
                return;
            }
        }
    }
    throw runtime_error("\033[1;31mLivro nao encontrado no acervo!\033[0m");
}
void Biblioteca::deletar_pedido_reserva(string identificaçao, string nome_livro) {
    for ( auto& pedido :pedidos_reserva){
        if(pedido->identificacao_usuario == identificaçao && pedido->livro_pedido->get_nome() == nome_livro){
            pedidos_reserva.remove(pedido);
            return;
        }
    }
}
void Biblioteca::deletar_pedido_renovar_emprestimo(string identificaçao, string nome_livro) {
    for ( auto& pedido :pedidos_renovar_emprestimo){
        if(pedido->identificacao_usuario == identificaçao && pedido->livro_pedido->get_nome() == nome_livro){
            pedidos_renovar_emprestimo.remove(pedido);
            return;
        }
    }
}
Usuario* Biblioteca::get_usuario(string identificacao) {
    for (const auto &usuario: usuarios) {
        if(usuario->get_identificacao() == identificacao){
            return usuario;
        }
    }
    return nullptr;
}
Funcionario* Biblioteca::get_funcionario(string identificacao){
    for (const auto &funcionario: funcionarios) {
        if(funcionario->get_identificacao() == identificacao){
            return funcionario;
        }
    }
    return nullptr;
}
