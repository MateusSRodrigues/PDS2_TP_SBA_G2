# PDS2_TP_SBA_G2


-  ![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
 ![Git](https://img.shields.io/badge/git-%23F05033.svg?style=for-the-badge&logo=git&logoColor=white)
 ![Visual Studio Code](https://img.shields.io/badge/Visual%20Studio%20Code-0078d7.svg?style=for-the-badge&logo=visual-studio-code&logoColor=white)
<h1 align="center"> TP-FINAL-PDS2-Biblioteca </h1>

  Esse repositório tem por finalidade criar um **Sistema de Biblioteca Avançado**, em C++, para apresentação de um trabalho em grupo de "Programação e Desenvolvimento de Software II", da UFMG.

## Problema
  O sistema de Biblioteca Avançado visa abordar os desafios enfrentados por bibliotecas modernas e seus membros. Nas bibliotecas tradicionais, os processos de reserva, empréstimo e devolução de livros geralmente são manuais, consumindo tempo tanto dos membros quanto dos funcionários. Além disso, a gestão de multas e o acompanhamento do catálogo de livros podem ser complexos. À medida que as bibliotecas buscam modernizar e melhorar a experiência do usuário, o gerenciamento eficiente se torna essencial.

  Este projeto se torna importante em um contexto onde a conveniência, eficiência e acessibilidade são essenciais. O sistema aborda as necessidades tanto de membros da biblioteca quanto de funcionários, proporcionando uma experiência aprimorada no processo de busca, reserva, retirada, devolução e avaliação de livros. Além disso, a funcionalidade de gerenciamento de multas e o opcional de reserva de salas de estudo atendem a uma ampla gama de requisitos das bibliotecas, tornando-o uma solução valiosa.

## Visão Geral da Solução

O sistema de Biblioteca Avançado é uma aplicação de software que abrange todas as operações-chave de uma biblioteca, tanto para membros quanto para funcionários. Sua estrutura geral compreende:

* Cadastro de Usuário: Os membros da biblioteca (funcionarios, professores e alunos), podem se cadastrar e fazer login em suas contas. Isso permite que eles acessem serviços e informações personalizadas. O cadastro pede nome completo, identificação, telefone e senha, para funcionarios ainda é pedido o turno de trabalho. A diferneciação de cadastro é feita pela identificação (5 numeros correspode a funcionario, 7 é professor e 9 é aluno).

* Pesquisa de Livros: Os usuários podem pesquisar livros por título, autor, categoria ou palavra-chave, tornando a busca por materiais de leitura mais eficiente.

* Reserva de Livros: Professores e alunos podem pedir para reservar livros de maneira online, verificando a disponibilidade, se o funcionario da biblioteca aprovar a reserva é enviada a confirmação e lembrança da data limite de retirada, caso o membro desista da reserva ela poderá ser cancelada.

* Retirada de Livros Online: Oferece a opção de ter acesso ao link do pdf dos livros sem passar pelo balcão da biblioteca e nem precisando de reserva, economizando tempo.

* Retirada de Livros Presencial: Funcionários são responsaveis por realizar empréstimos presencialmente, apenas inserindo a identificação do membro e dando baixa no emprestimo dele, é enviada ao membro a confirmação e lembrança da data limite de devolução.

* Devolução de Livros Presencial: Funcionários são responsaveis por receber devoluções, apenas inserindo a identificação do membro e dando baixa na devolução e atualizando o status do livro e adicionar a lançando a avaliação do livro, feita pelo membro.

* Renovação de Empréstimo: Membros podem pedir para renovar empréstimos online, no entanto não podem renovar mais de uma vez seguida o mesmo livro e não podem realizar o pedido caso esteja devendo a biblioteca, o pedido poderá ser aceito ou negado por um funcionário.

* Gerenciamento de Multas: Funcionários podem ver as multas de qualquer membro ao pesquisar pela identificação dele nas informaçoes de ususario, eles também podem dar baixa no pagamento das multas ao receber presencialmente.

* Cadastro de Novos Livros: Funcionários podem cadastrar novos livros com informações detalhadas, incluindo título, autor, identificação, estado fisico e ano.

Este sistema visa simplificar e agilizar o gerenciamento de uma biblioteca, melhorar a experiência dos usuários e fornecer uma solução completa para as necessidades em constante evolução de bibliotecas modernas. A combinação de funcionalidades online e presenciais o torna uma ferramenta valiosa para qualquer instituição que deseje oferecer serviços de biblioteca mais eficientes e convenientes.

## User stories
 
 https://docs.google.com/document/d/1mkruYu_dgSMFSchUCw5HQvn-L3VfDcKsz3SXm98Ct_c/edit

## Cartão CRC

https://drive.google.com/file/d/1Cx5NkLtnsqqZ5Ss5SC3d4EOU6NWmZykV/view?usp=drive_link
///explicar mudanças

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






  


