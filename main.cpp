#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "SystemCore.h"
using namespace std;

void carregaMenuHd();
int main();
void printHelp();

int carregaMenuHd(char nome[], SystemCore sysHdCore){
	string cmd, complementoTemp;
	char complemento[30];
	
	while(1){
		cout<<nome<<"> ";
		cin>>cmd;
		
		for(int k=0; k<cmd.size(); k++){
			cmd[k] = tolower(cmd[k]);	
		}
		
		if(cmd != "#" && cmd != "root" && cmd != "limpar" && cmd != "help"){
			cin>>complementoTemp;
			
			for(int k=0; k<complementoTemp.size(); k++){
				complementoTemp[k] = tolower(complementoTemp[k]);	
			}
		}
		
		if(cmd == "#" || cmd == "root"){
			printf("\n\tSaindo..\n\n");
			return 1;
		}
		else if(cmd == "create"){
			int i;
			for(i=0; i<complementoTemp.size(); i++){
				complemento[i] = complementoTemp[i];
			}
			complemento[i] = 0;
			
			sysHdCore.CriarArquivo(complemento);
			// CHAMADA DO OBJETO
		}
		else if(cmd == "remove"){
			int i;
			for(i=0; i<complementoTemp.size(); i++){
				complemento[i] = complementoTemp[i];
			}
			complemento[i] = 0;
			
			sysHdCore.RemoveArquivo(complemento);
		}
		else if(cmd == "type"){
			int i;
			for(i=0; i<complementoTemp.size(); i++){
				complemento[i] = complementoTemp[i];
			}
			complemento[i] = 0;
			
			sysHdCore.TypeArquivo(complemento);
		}
		else if(cmd == "help"){
			printHelp();
		}
		else if(cmd == "limpar"){
			system("cls");
		}
		else{
			printf("\n\tComando invalido.\n\tUtilize o comando help para visualizar todos os comandos.\n\n");
		}	
	}
	
}

void printHelp(){
	// GERAL
	printf("\n-> Help menu GERAL\n");
	printf("\t limpar    [command]                    ");
	printf("\t -> limpa a tela\n\n");
	
	printf("\t exit      [command]                    ");
	printf("\t -> Sair (apenas a partir do diretorio root)\n\n");
	
	// HD
	printf("\n-> Help menu HD\n");
	printf("\t listhd    [command]                    ");
	printf("\t -> Lista os HDs disponiveis\n\n");
	
	printf("\t selecthd  [command][nome_HD]           ");
	printf("\t -> Seleciona o HD desejado\n\n");
	
	printf("\t createhd  [command][nome_HD]           ");
	printf("\t -> Cria um HD com o nome especificado\n\n");
	
	printf("\t formathd  [command][nome_HD]           ");
	printf("\t -> formata o HD desejado\n\n");
	
	printf("\t typehd    [command][nome_HD]           ");
	printf("\t -> Mostra os blocos utilizados do HD\n");
	
	// ARQUIVOS
	printf("\n");
	printf("\n-> Help menu Arquivos (Apenas quando tem um HD ja selecionado)\n");
	printf("\t create    [command][nome_arquivo]      ");
	printf("\t -> Cria um arquivo com o nome especificado\n\n");
	
	printf("\t remove    [command][nome_arquivo]      ");
	printf("\t -> Remove o arquivo com o nome especificado\n\n");
	
	printf("\t type      [command][nome_arquivo]      ");
	printf("\t -> Mostra o conteudo do arquivo\n\n");
	
	printf("\t # ou root [command]                    ");
	printf("\t -> Sai do HD selecionado\n\n");
	
	printf("\n");
}

int main() {
	SystemCore sysHdCore;
	
	string cmd, complementoTemp;
	char complemento[10];
	bool loop = true;
	
	printf("EPSILON (Centro universitario FEI) - @FelipeDantas\n\n");
	printf("Se desejar, digite help para listar os comandos.\n\n");
	while(loop){
		printf("#> ");

		cin>>cmd;
		
		for(int k=0; k<cmd.size(); k++){
			cmd[k] = tolower(cmd[k]);	
		}
		
		if(cmd != "help" && cmd != "exit" && cmd != "listhd" && cmd != "limpar" && cmd != "root" && cmd != "#"){
			cin>>complementoTemp;
			
			for(int k=0; k<complementoTemp.size(); k++){
				complementoTemp[k] = tolower(complementoTemp[k]);	
			}
		}
		
		if(cmd == "listhd"){
			sysHdCore.ListHd();
		}
		else if(cmd == "selecthd"){
			int i;
			for(i=0; i<complementoTemp.size(); i++){
				complemento[i] = complementoTemp[i];
			}
			complemento[i] = 0;
				
			if(sysHdCore.inicializarHd(complemento))
				carregaMenuHd(complemento, sysHdCore);
		}
		else if(cmd == "createhd"){
			int i;
			for(i=0; i<complementoTemp.size(); i++){
				complemento[i] = complementoTemp[i];
			}
			complemento[i] = 0;
				
			sysHdCore.CriarHd(complemento);
			carregaMenuHd(complemento, sysHdCore);
		}
		else if(cmd == "formathd"){
			int i;
			for(i=0; i<complementoTemp.size(); i++){
				complemento[i] = complementoTemp[i];
			}
			complemento[i] = 0;
			
			sysHdCore.FormatarHd(complemento);
		}
		else if(cmd == "typehd"){
			int i;			
			for(i=0; i<complementoTemp.size(); i++){
				complemento[i] = complementoTemp[i];
			}
			complemento[i] = 0;
			
			sysHdCore.TypeHd(complemento);
			
		}
		else if(cmd == "help"){
			printHelp();
		}
		else if(cmd == "limpar"){
			system("cls");
		}
		else if(cmd == "root" || cmd == "#"){
			
		}
		else if(cmd == "exit"){
			loop = false;
			exit;
			cout<<"\n\tEncerrando.."<<endl;
		}
		else{
			printf("\n\tComando invalido.\n\tUtilize o comando help para visualizar todos os comandos.\n\n");
		}
	}
	return 0;
}
