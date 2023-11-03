#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <unistd.h>

using namespace std;
string menu(vector<string>& opcao,  vector<string>& cabecalho){
        char n;
        int c;
        for (int i = 0; i < cabecalho.size(); i++) {
            cout << cabecalho[i] << " ";
        }
        cout << endl << "============================"<< endl << "->";
        for (int i = 0; i < opcao.size(); i++) {
            cout << opcao[i] << endl;
        }
        cout << "###############################"<< endl << "###############################" << endl;
        while (n = getch()) {
            system("cls");
            switch (n) {
                case 'v':
                    c++;              ///altera contador de click, desc a seta
                    break;

                case 'f':
                    c--;              ///altera contador de click,  sub a seta
                    break;

                case 'x':             ///escolhe opçao
                  if (c==0) {
                      return opcao[0];
                  }else
                  return opcao[c % opcao.size()];

                    break;
            }

            for (int i = 0; i < opcao.size(); i++) {        ///loop imprime a lista de opçoes

                if (i == 0) {                           /// para i=0 limpa tela e impime cabeçalho
                    for (int i = 0; i < cabecalho.size(); i++) {
                        cout << cabecalho[i] << " ";
                    }
                    cout << endl << "============================"<< endl;
                }
                if (i == c % opcao.size()) {        /// calcula e imprime seta
                    cout << "->";
                    cout << opcao[i] << endl;
                } else{                         /// imprime restante
                    cout << opcao[i]<< endl;
                }
                if (i == opcao.size()-1) {
                    cout << "###############################"<< endl << "###############################"<< endl;
                }
            }
        }
}
int main() {
    float num;
    cin >> num;
    string s = to_string(num);
    s.resize(s.size()-4);
    vector <string> opca = {"sim", "nao","sempre"};
    vector<string> cabec = {"Sua multa atual esta no valor de ", s,"deseja pagar agora?"};
    cout << menu(opca, cabec);
    return 0;
}

