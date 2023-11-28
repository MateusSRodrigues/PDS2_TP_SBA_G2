//
// Created by rayda on 02/11/2023.
//
#include <iomanip>
#include <unistd.h>
#include <cmath>
#include "Usuario.h"
#include "Biblioteca.h"

Usuario::Usuario(string n, string sen, string t, string id) : Pessoa(n, sen, t, id) {
}
void Usuario::mostrar_informacoes_de_cadastro() {
    cout << setprecision(2) << fixed;
    cout << "###############################################" << endl << "\033[0;35mSuas informacoes.\033[0m" << endl << "-----------------------------" << endl;
    cout << "\033[0;35mNome: \033[0m \033[32m" << get_nome() << ".\033[0m" << endl << "\033[0;35mIdentificacao: \033[0m \033[32m" << get_identificacao() << ".\033[0m" << endl;
    cout << "\033[0;35mTipo de usuario: \033[0m \033[32m";
    if(get_identificacao().size() == 9){cout<< "Aluno.\033[0m" << endl;}
    else if(get_identificacao().size() == 7){cout << "Professor.\033[0m" << endl;}
    cout << "\033[0;35mTelefone: \033[0m \033[32m" << get_telefone() << ".\033[0m" << endl << "\033[0;35mValor multa: \033[0m \033[31m" << valor_multa << ".\033[0m" << endl;
    cout << "\033[0;35mLivro(s) reservados:  \033[0m";
    try{
   ver_livros_reservados();
        }catch (const exception &e) {
       cerr << e.what() << endl;
       cin.clear();
    }
    cout << "\033[0;35mLivro(s) em posse:  \033[0m";
    ver_livros_emprestados();
    cout << "###############################################" << endl;
}
float Usuario::get_valor_multa() {
    return valor_multa;
}
void Usuario::pagar_multa() {
    vector <string> opcao ={"Sim.", "Nao."};
    string valor = to_string(valor_multa);
    valor.resize(valor.size()-4);
    vector <string> cabec = {"Voce esta devendo ", valor, ", quer pagar agora?"};
    string resposta = menu2(opcao, cabec);
    if(resposta == "Sim."){
        float valor_a_pagar;
        cout << "deseja pagar quanto?" << endl;
        cin >> valor_a_pagar;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw invalid_argument("\033[1;31mVoce inseriu um valor invalido.\033[0m");
        }
        if(valor_a_pagar > valor_multa){
            throw invalid_argument("\033[1;31mVoce inseriu um valor acima do devido.\033[0m");
        }else{
            valor_multa -= valor_a_pagar;
            cout.precision(2);
            cout << fixed << "Voce pagou " << valor_a_pagar << ". Sua multa atual e de " << valor_multa << endl;
        }
        return;
    }
    if(resposta == "Nao."){
        return;
    }
}
int Usuario::get_tamanho_reservados() {
    return livros_reservados.size();
}
int Usuario::get_tamanho_emprestados() {
    return livros_em_uso.size();
}
void Usuario::ver_livros_emprestados() {
    if (!livros_em_uso.empty()) {
        cout << "\033[32mLivro(s) em posse: \033[0m";
        for (const auto &livro : livros_em_uso) {
            cout << "\033[32m" << livro->get_nome() << ", \033[0m";
        }
        cout << "\033[32m.\033[0m" << endl;
    } else {
        throw runtime_error ("\033[1;31mNao ha livros em sua posse!\033[0m");
    }
}
void Usuario::ver_livros_reservados() {
    if (!livros_reservados.empty()) {
        cout << "\033[32mLivro(s) reservados: \033[0m";
        for (const auto &livro : livros_reservados) {
            cout << "\033[32m" << livro->get_nome() << ", \033[0m";
        }
        cout << "\033[32m.\033[0m" << endl;
    } else {
        throw runtime_error ("\033[1;31mNao ha livros reservados!\033[0m");
    }
}
void Usuario::adicionar_aviso(string msg) {
    avisos.push_back(msg);
}
void Usuario::ler_avisos(Biblioteca* b) {
    system("cls");
    int i = 1;
    //for (auto& aviso : avisos) {
    for (auto aviso = avisos.begin(); aviso != avisos.end(); ++aviso) {
        int nao_achou = 1000;
        if(aviso->find("que voce pediu para reservar nao existe mais nenhum exemplar disponivel") > nao_achou){     /// quando o find n encontra ele retorna uma valor alto, o aviso sempre tem menos de 1000 caracteres
            vector<string> opcao = {"Sim", "Nao"};
            vector<string> cabecalho_apagar = {"\033[33maviso", to_string(i), ": \033[0m", *aviso, "\n","\033[33m-------------------------------------\033[0m","\n","Deseja apagar este aviso?"};
            string resposta = menu2(opcao, cabecalho_apagar);
            if(resposta == "Sim"){
                avisos.erase(aviso);
                aviso--;
            }
        } else if(aviso->find("que voce pediu para reservar nao existe mais nenhum exemplar disponivel") < nao_achou){
            vector<string> opcao = {"Sim", "Nao"};
            vector<string> cabecalho_escolha = {*aviso};
            if(menu2(opcao, cabecalho_escolha) == "Nao"){
                string nome_livro = *aviso;
                nome_livro.erase (nome_livro.begin(), nome_livro.begin() + 8);  /// retira "o livro "
                nome_livro.erase(nome_livro.begin()+nome_livro.find(" que voce pediu para reservar nao existe"),nome_livro.end());           /// retira " que voce ..."
                b->deletar_pedido_reserva(this->get_identificacao(), nome_livro);
            }
            avisos.erase(aviso);
            aviso--;
            i--;
        }
        i++;
    }
}
void Usuario::adicionar_livro_reservado(Livro *l) {
    livros_reservados.push_back(l);
}
string Usuario::mostrar_livros_reservados(string acao) {
    vector<std::string> lista_emprestados;
    vector<string> cabecalho_reservados = {"Deseja ", acao,  "de qual livro?"};
    if (livros_reservados.empty()) {
        cout << "\033[1;31mNenhum livro encontrado!\033[0m" << endl;
        return "vazio";
    } else {
        for (const auto& livro : livros_reservados) {
            lista_emprestados.push_back(livro->get_nome());
        }
        return menu2(lista_emprestados,cabecalho_reservados);
    }
}
string Usuario::mostrar_livros_em_uso(string acao) {
    vector<std::string> lista_em_uso;
    vector<string> cabecalho_em_uso = {"Deseja ", acao, " qual livro?"}; ///////////////
    if (livros_em_uso.empty()) {
        cout << "\033[1;31mNenhum livro encontrado!\033[0m" << endl;
        return "vazio";
    } else {
        for (const auto& livro : livros_em_uso) {
            lista_em_uso.push_back(livro->get_nome());
        }
        return menu2(lista_em_uso,cabecalho_em_uso);
    }
}
void Usuario::reservar_livro(Biblioteca* b) {
    // Mostra a lista de livros disponíveis na biblioteca
    Livro* livro_escolhido = b->mostrar_exemplar_todos_livros();
    if(livro_escolhido != nullptr) {
        for (auto &livro_ptr: livros_reservados) {
            if (livro_escolhido->get_nome() == livro_ptr->get_nome()) {
                cout << "\033[1;31mVoce nao pode reservar esse livro, pois ja possui um deste mesmo nome reservado!\033[0m"<< endl;
                return;
            }
        }
        for (auto &livro_ptr: livros_em_uso) {
            if (livro_escolhido->get_nome() == livro_ptr->get_nome()) {
                cout << "\033[1;31mVoce nao pode reservar esse livro, pois ja pegou emprestado um de mesmo nome!\033[0m" << endl;
                return;
            }
        }
        vector<string> opcao = {"Sim", "Nao"};
        vector<string> cabecalho = {"Deseja entrar para a fila de espera para reservar este livro?"};
        string resposta = menu2(opcao, cabecalho);
        if (resposta == "Nao") {
            cout << "Voce nao quer reservar este livro." << endl;
            return;
        } else if (resposta == "Sim") {       /// Cria o pedido de reserva
            b->criar_pedido_reserva(this->get_identificacao(), livro_escolhido);
            return;
        }
    } if (livro_escolhido == nullptr) {
        throw runtime_error ("\033[1;31mNao ha livros!\033[0m");
    }
}
void Usuario::cancelar_reserva() {
    string s = mostrar_livros_reservados("cancelar a reserva ");
    if(s != "vazio") {
        for (auto &livro_ptr: livros_reservados) {
            if (livro_ptr->get_nome() == s && livro_ptr->get_estado_emprestimo() == "Reservado") {
                livro_ptr->set_estado_emprestimo("Disponivel");

                livros_reservados.remove(livro_ptr);
                cout << "\033[32mReserva livro cancelada com sucesso.\033[0m" << endl;
                return;
            }
        }
    }
}
void Usuario::retirar_livro() {
    string s = mostrar_livros_reservados("retirar ");
    for (auto& livro_ptr : livros_reservados) {
        if (livro_ptr->get_nome() == s && livro_ptr->get_estado_emprestimo() == "Reservado") {
            livro_ptr->set_estado_emprestimo("Emprestado");
            /// manda aviso de vencimento pro usuario.
            livro_ptr->atribui_data_emprestimo();
            stringstream str_vencimento;
            str_vencimento << put_time(livro_ptr->get_data_vencimento(), "%d/%m/%Y");
            string aviso = "Voce retirou o livro da biblioteca. A data de vencimento do seu imprestimo e " + str_vencimento.str() + ".";
            adicionar_aviso(aviso);
            livros_em_uso.push_back(livro_ptr);
            cout << "\033[32mlivro emprestado com sucesso!\033[0m" << endl;
            livros_reservados.remove(livro_ptr);
            return;
        }
    }
}
void Usuario::devolver_livro(Biblioteca* b1) {  /// por grande parte essa funçao no funcionario ela deve retornar o livro e funcionario fazer td.
    if(livros_em_uso.empty()){
        throw runtime_error ("\033[1;31mNao ha livros em sua posse!\033[0m");
    }
    string s = mostrar_livros_em_uso("devolver");
    for (auto& livro_ptr : livros_em_uso) {
        if (livro_ptr->get_nome() == s && livro_ptr->get_estado_emprestimo() == "Emprestado") {
            livro_ptr->set_estado_emprestimo("Disponivel");
            // Obtendo a data atual
            chrono::system_clock::time_point now = chrono::system_clock::now();
            time_t data_atual = chrono::system_clock::to_time_t(now);
            tm* data_atual_tm = localtime(&data_atual);
            // Convertendo ambas as datas para time_t para cálculos
            time_t time1 = mktime(livro_ptr->get_data_vencimento());
            time_t time2 = mktime(data_atual_tm);
            // Calculando a diferença em segundos
            chrono::seconds diff = chrono::seconds(time2 - time1);
            // Convertendo a diferença para dias
            int dias = chrono::duration_cast<chrono::hours>(diff).count() / 24;
            // aplica multa
            if(dias > 0){
                float valor_diaria = 0.3;
                float multa_recebida = trunc(dias) * valor_diaria;
                valor_multa += multa_recebida;
                string str_multa = to_string(multa_recebida);
                str_multa.resize(str_multa.size()-4);
                string aviso = "Voce devolveu o livro " + to_string(dias) + " dias atrasado, recebeu uma multa de " + str_multa + ".";
                adicionar_aviso(aviso);
                livro_ptr->zerar_datas_livro();
            }
            //avalia livro
            vector<string> opcao_avaliar ={"0", "1","2","3","4","5","6","7","8","9","10"};
            vector<string> cabecalho_nota = {"Qual a nota de 0 a 10 que o usuario da para o livro?"};
            livro_ptr->receber_avaliacao(stoi(menu2(opcao_avaliar,cabecalho_nota)));
            //avalia estado fisico livro
            vector<string> opcao_ef ={"Pessimo", "Ruim","Medio","Bom","Otimo"};
            vector<string> cabecalho_estado = {"Qual o estado fisico deste livro?"};
            livro_ptr->set_estado_fisico(menu2(opcao_ef,cabecalho_estado));
            b1->deletar_pedido_renovar_emprestimo(get_identificacao(), livro_ptr->get_nome());

            //deleta livro
            livros_em_uso.remove(livro_ptr);
            cout << "\033[32mlivro devolvido com sucesso!\033[0m" << endl;
            return;
        }
    }
}
void Usuario::renovar_emprestimo(Biblioteca* b1) {
    string s = mostrar_livros_em_uso("renovar pedido de");
    if(s != "vazio") {
        for (auto &livro_ptr: livros_em_uso) {
            if (livro_ptr->get_nome() == s) {
                if (b1->pedido_renovar_emprestimo_efetuado(livro_ptr->get_nome(), this->get_identificacao())) {
                    cout << "\033[1;31mVoce ja fez um pedido de renovacao deste livro.\033[0m" << endl;
                    return;
                } else {
                    b1->criar_pedido_renovar_emprestimo(this->get_identificacao(), livro_ptr);
                    return;
                }
            }
        }
    }
}
void Usuario::atualizar() {
    for (const auto &livro_ptr: livros_reservados) {                /// retira dos livros reservados os que foram reservados ha mais de 3 dias
        if(!livros_reservados.empty()){
            // Obtendo a data atual
            chrono::system_clock::time_point now = chrono::system_clock::now();
            time_t data_atual = chrono::system_clock::to_time_t(now);
            tm *data_atual_tm = localtime(&data_atual);
            // Convertendo ambas as datas para time_t para cálculos
            time_t time1 = mktime(livro_ptr->get_data_reserva());
            time_t time2 = mktime(data_atual_tm);
            // Calculando a diferença em segundos
            chrono::seconds diff = chrono::seconds(time2 - time1);
            // Convertendo a diferença para dias
            int dias = chrono::duration_cast<chrono::hours>(diff).count() / 24;
            if (dias > 3 ) {
                livro_ptr->zerar_datas_livro();
                string aviso = "Sua reserva do livro " + livro_ptr->get_nome() + " foi expirada!";
                adicionar_aviso(aviso);
                livros_reservados.remove(livro_ptr);
                return;
            }
        }
    }
    return;
}
bool Usuario::algum_livro_vencido() {
    for (const auto &livro_ptr: livros_em_uso) {                /// retira dos livros reservados os que foram reservados ha mais de 3 dias
        // Obtendo a data atual
        chrono::system_clock::time_point now = chrono::system_clock::now();
        time_t data_atual = chrono::system_clock::to_time_t(now);
        tm *data_atual_tm = localtime(&data_atual);
        // Convertendo ambas as datas para time_t para cálculos
        time_t time1 = mktime(livro_ptr->get_data_vencimento());
        time_t time2 = mktime(data_atual_tm);
        // Calculando a diferença em segundos
        chrono::seconds diff = chrono::seconds(time2 - time1);
        // Convertendo a diferença para dias
        int dias = chrono::duration_cast<chrono::hours>(diff).count() / 24;
        if (dias > 0) {
            return true;
        }
    }
    return false;
}
void Usuario::retirar_livro_online(Biblioteca *b1) {
    Livro* l = b1->mostrar_exemplar_todos_livros();
    if(l != nullptr) {
        cout << "link livro: " << l->get_nome() << ": " << l->get_link() << endl;
    }else {
        runtime_error("\033[1;31mNao ha livros no acervo!\033[0m");
    }
}





