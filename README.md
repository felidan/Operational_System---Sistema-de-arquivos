Sistema de arquivos
===================================================

Este programa foi desenvolvido como um trabalho para a matéria de **Sistemas Operacionais (SO)** do Centro universitário da FEI no intuito de simular um sistema de alocação de arquivos baseado no modelo de **alocação contígua** (Alocação sequencial na memória).

A organização da memória é dividida em duas partes:
   -> blocos iniciais são reservados para o nome dos arquivos e endereço de início do arquivo. O restante dos blocos é reservado para o conteúdo dos arquivos em si.
   
## Requisitos

* Compilador - **GCC 4.9.2** igual ou superior (esta versão já está disponível na versão 5.11 ou superior do Dev C++);
* Sistema operacional **Windows**.

Ao criar um novo HD virtual o mesmo fica disponível no diretório **/HDVirtual** na raiz no projeto (arquivos com a extensão **.flp**).

## Comandos disponíveis na versão 1.0 (utilize o comando help para uma descrição mais detalhada dos comandos):

* limpar;
* exit;
* listhd - lista os HDs existentes;
* selecthd - seleciona um HD;
* createhd - cria um novo HD;
* formathd - formata um HD existente;
* typehd - imprime blocos utilizados do HD;
* create - cria um novo arquivo;
* remove - remove um arquivo existente;
* type - visualiza o arquivo;
* # ou root - sai do HD.

