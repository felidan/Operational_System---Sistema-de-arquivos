#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <exception>
#include "ascii.h"

#define MAX_BLOCO_DIR 100 // Quantidade de blocos reservados para diretório
#define MAX_BLOCO_ARQ 900 // Quantidade de blocos reservados para arquivos
#define MAX_TAMANHO_BLOCO 32 // tamanho do bloco

using namespace std;

#ifndef SYSTEM_CORE
#define SYSTEM_CORE

class SystemCore{
	private:
		char blocoDiretorio[MAX_BLOCO_DIR][MAX_TAMANHO_BLOCO];
		char blocoArquivo[MAX_BLOCO_ARQ][MAX_TAMANHO_BLOCO];
		char nomeHd[30];
		string PATH;
	public:
		SystemCore();
		// manipulação do HD
		void ListHd();
		bool inicializarHd(char nome[]);
		bool CriarHd(char nome[]);
		bool FormatarHd(char nome[]);
		bool TypeHd(char nome[]);
		void Salvar(char nome[]);
		
		// manipulação de arquivos
		bool CriarArquivo(char nome[]);
		bool RemoveArquivo(char nome[]);
		bool TypeArquivo(char nome[]);
		
		// manipulação de blocos
		int FindBlocoDirVazio();
		int FindBlocoArqVazio(int QtBloco);
		int FindArquivoPorNome(char nome[]);
		
		~SystemCore();
};

#endif
