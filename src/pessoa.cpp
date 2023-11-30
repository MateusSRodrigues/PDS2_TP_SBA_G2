#include "pessoa.h"

Pessoa::Pessoa(string n, string sen, string t, string id) : nome(n), senha(sen), telefone(t), identificacao(id) {
}
string Pessoa::get_nome() {
    return nome;
}
string Pessoa::get_telefone() {
    return telefone;
}
string Pessoa::get_senha() {
    return senha;
}
string Pessoa::get_identificacao() {
    return identificacao;
}




