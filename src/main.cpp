#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <unistd.h>
using namespace std;
string pagar_multa(float valor_multa, vector<string>& opcao){
        char n;
        int c;
        cout << "Sua multa atual esta no valor de " << valor_multa << " deseja pagar agora?" << endl;
        cout << "============================"<< endl << "->";
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
                    cout << "Sua multa atual esta no valor de " << valor_multa << " deseja pagar agora?" << endl;
                    cout << "============================"<< endl;
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
    vector <string> opca = {"sim", "nao","sempre"};
    cout << pagar_multa(15,opca);

    return 0;
}
