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
