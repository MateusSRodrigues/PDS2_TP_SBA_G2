# PDS2_TP_SBA_G2


-  ![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
 ![Git](https://img.shields.io/badge/git-%23F05033.svg?style=for-the-badge&logo=git&logoColor=white)
 ![Visual Studio Code](https://img.shields.io/badge/Visual%20Studio%20Code-0078d7.svg?style=for-the-badge&logo=visual-studio-code&logoColor=white)
<h1 align="center"> TP-FINAL-PDS2-Biblioteca </h1>

  Esse repositório tem por finalidade criar um **Sistema de Biblioteca**, em C++, para apresentação de um trabalho em grupo de "Programação e Desenvolvimento de Software II", da UFMG.

## Problema
  O sistema de Biblioteca Avançado visa abordar os desafios enfrentados por bibliotecas modernas e seus membros. Nas bibliotecas tradicionais, os processos de reserva, empréstimo e devolução de livros geralmente são manuais, consumindo tempo tanto dos membros quanto dos funcionários. Além disso, a gestão de multas e o acompanhamento do catálogo de livros podem ser complexos. À medida que as bibliotecas buscam modernizar e melhorar a experiência do usuário, o gerenciamento eficiente se torna essencial.

  Este projeto se torna importante em um contexto onde a conveniência, eficiência e acessibilidade são essenciais. O sistema aborda as necessidades tanto de membros da biblioteca quanto de funcionários, proporcionando uma experiência aprimorada no processo de busca, reserva, retirada, devolução e avaliação de livros. Além disso, a funcionalidade de gerenciamento de multas e o opcional de reserva de salas de estudo atendem a uma ampla gama de requisitos das bibliotecas, tornando-o uma solução valiosa.

## Visão Geral da Solução

O sistema de Biblioteca Avançado é uma aplicação de software que abrange todas as operações-chave de uma biblioteca, tanto para membros quanto para funcionários. Sua estrutura geral compreende:

* Cadastro de Usuário: Os membros da biblioteca, incluindo professores e alunos, podem se cadastrar e fazer login em suas contas. Isso permite que eles acessem serviços e informações personalizadas.

* Pesquisa de Livros: Os usuários podem pesquisar livros por título, autor, categoria ou palavra-chave, tornando a busca por materiais de leitura mais eficiente.

* Reserva de Livros: Membros da biblioteca podem reservar livros online, verificando a disponibilidade, recebendo confirmações e lembranças das datas de retirada.

* Retirada de Livros Online: Oferece a opção de retirar livros sem passar pelo balcão da biblioteca, economizando tempo.

* Retirada de Livros Presencial: Funcionários podem gerenciar empréstimos presencialmente, verificar a disponibilidade, identificar usuários e gerar recibos.

* Devolução de Livros Presencial: Funcionários podem receber devoluções, verificar datas, aplicar multas, atualizar o status do livro e fornecer comprovantes de devolução.

* Renovação de Empréstimo: Membros podem renovar empréstimos online, desde que não haja reservas pendentes.

* Avaliação de Livros (Opcional): Membros podem atribuir classificações a livros e ver as classificações de outros membros ao pesquisar no catálogo.

* Gerenciamento de Multas: Funcionários podem gerenciar multas, incluindo notificações, registro de pagamento e geração de relatórios.

* Reserva de Salas de Estudo (Opcional): Membros podem reservar salas de estudo online, com confirmações e opções de cancelamento.

* Cadastro de Novos Livros: Funcionários podem cadastrar novos livros com informações detalhadas, incluindo título, autor, editora, ISBN e disponibilidade inicial.

Este sistema visa simplificar e agilizar o gerenciamento de uma biblioteca, melhorar a experiência dos usuários e fornecer uma solução completa para as necessidades em constante evolução de bibliotecas modernas. A combinação de funcionalidades online e presenciais o torna uma ferramenta valiosa para qualquer instituição que deseje oferecer serviços de biblioteca mais eficientes e convenientes.

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






  


