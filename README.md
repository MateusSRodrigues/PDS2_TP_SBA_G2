# PDS2_TP_SBA_G2


-  ![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
 ![Git](https://img.shields.io/badge/git-%23F05033.svg?style=for-the-badge&logo=git&logoColor=white)
 ![Visual Studio Code](https://img.shields.io/badge/Visual%20Studio%20Code-0078d7.svg?style=for-the-badge&logo=visual-studio-code&logoColor=white)
<h1 align="center"> TP-FINAL-PDS2-Biblioteca </h1>

  Esse repositório tem por finalidade criar um **Sistema de Biblioteca**, em C++, para apresentação de um trabalho em grupo de "Programação e Desenvolvimento de Software II", da UFMG.



## Resumo
O sistema de Biblioteca Avançado é um sistema completo de gerenciamento de bibliotecas que atende às necessidades de membros da biblioteca e funcionários. Ele oferece diversas funcionalidades, incluindo:

* Reserva de Livros: Membros podem reservar livros online, verificar a disponibilidade e receber confirmações, além de serem lembrados da data de retirada.

* Retirada de Livros Online: Permite que membros retirem livros online, economizando tempo e oferecendo conveniência.

* Retirada de Livros Presencial: Funcionários podem emprestar livros fisicamente, verificar disponibilidade, identificar usuários e gerar recibos.

*  Devolução de Livros Presencial: Funcionários podem receber devoluções, verificar datas, aplicar multas, atualizar status do livro e fornecer comprovantes de devolução.

* Renovação de Empréstimo: Membros podem renovar empréstimos online, sujeito a regras de reserva.

* Avaliação de Livros: Membros podem avaliar os livros, compartilhando opiniões e visualizando as classificações de outros membros.

* Gerenciamento de Multas: Funcionários podem gerenciar multas, incluindo visualização, registro de pagamento e geração de relatórios.

* Reserva de Salas de Estudo (Opcional): Membros podem reservar salas de estudo online.

* Cadastro de Novos Livros: Funcionários podem cadastrar novos livros com informações detalhadas.

* Cadastro de Usuário: Usuários podem se cadastrar, fazer login e pesquisar livros.

* Cadastro de Professor (Opcional): Professores podem se registrar para acesso a recursos especiais.

* Cadastro de Aluno (Opcional): Alunos podem se registrar para acesso a empréstimos e pesquisa.

* Multa: Sistema de multas por atraso na devolução de livros, com notificações, cálculo de multas, registro e bloqueio de privilégios.

O sistema é abrangente e atende às necessidades de gerenciamento de bibliotecas, oferecendo funcionalidades online e presenciais para membros e funcionários. Além disso, inclui recursos adicionais, como reserva de salas de estudo e a opção de cadastrar professores e alunos para serviços diferenciados. É uma solução completa para melhorar a eficiência e conveniência de uma biblioteca moderna.


 ## Pré-requisitos
  Para usar o sistema é preciso ter um compilador de C++ e makefile
  ## **Ferramentas**

Esse projeto utiliza as seguintes linguagem, ferramentas e bibliotecas:

* Linguagem: [C++11](https://cplusplus.com/doc/)
* Compilação: [Make](https://www.gnu.org/software/make/)
* Documentação: [Doxygen](https://doxygen.nl/)
* Testes Unitários: [Doctest](https://github.com/doctest/doctest)
* Cobertura: [gcovr](https://gcovr.com/)

## **Compilação**

```bash
$ make
```

**Atenção: Criar antes um diretório _./build/_** (mkdir build)

## **Execução**

```bash
$ make run
```

## **Compilação Testes**

```bash
$ make tests
```

## **Execução Testes**

```bash
$ make run_tests
```

## **Relatório de Cobertura**

Para imprimir o relatório simplificado no próprio Terminal, utilizar:
```bash
$ make coverage
```

Para gerar o relatório em HTML, utilizar:
```bash
$ make html_coverage
```
## **Remover arquivos auxiliares**
```bash
$ make clean
```






  


