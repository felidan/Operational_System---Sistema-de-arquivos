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
	
	string cmd, complementoTemp, complementoTempTwo;
	char complemento[30],complementoTwo[30], stringFake[1];
	while(1){
		cout<<nome<<"> ";
		
		// Primeiro comando
		cin>>cmd;
		
		for(int k=0; k<cmd.size(); k++){
			cmd[k] = tolower(cmd[k]);	
		}
		
		if(cmd != "#" && cmd != "root" && cmd != "limpar" && cmd != "help" && cmd != "dir" && cmd != "typehd" && cmd != "status"){
			// Segundo comando
			cin>>complementoTemp;
			
			for(int k=0; k<complementoTemp.size(); k++){
				complementoTemp[k] = tolower(complementoTemp[k]);	
			}
			
			if(cmd == "copy" || cmd == "rename"){
				// Terceiro comando
				cin>>complementoTempTwo;
				
				for(int k=0; k<complementoTempTwo.size(); k++){
					complementoTempTwo[k] = tolower(complementoTempTwo[k]);	
				}
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
			
			sysHdCore.CriarArquivo(complemento, stringFake, 0);
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
		else if(cmd == "dir"){
			sysHdCore.Dir();
		}
		else if(cmd == "status"){
			sysHdCore.StatusHd();
		}
		else if(cmd == "typehd"){
			sysHdCore.TypeHd(stringFake, 1);
		}
		else if(cmd == "copy"){
			int i;
			
			for(i=0; i<complementoTemp.size(); i++){
				complemento[i] = complementoTemp[i];
			}
			complemento[i] = 0;
			
			for(i=0; i<complementoTempTwo.size(); i++){
				complementoTwo[i] = complementoTempTwo[i];
			}
			complementoTwo[i] = 0;
			
			sysHdCore.CopiaArquivo(complemento, complementoTwo);
		}
		else if(cmd == "rename"){
			int i;
			
			for(i=0; i<complementoTemp.size(); i++){
				complemento[i] = complementoTemp[i];
			}
			complemento[i] = 0;
			
			for(i=0; i<complementoTempTwo.size(); i++){
				complementoTwo[i] = complementoTempTwo[i];
			}
			complementoTwo[i] = 0;
			
			sysHdCore.RenameArquivo(complemento, complementoTwo);
		}
		else if(cmd == "edit"){
			int i;
			
			for(i=0; i<complementoTemp.size(); i++){
				complemento[i] = complementoTemp[i];
			}
			complemento[i] = 0;
			
			sysHdCore.EditArquivo(complemento);
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
	printf("\t -> limpa a tela\n");
	
	printf("\t exit      [command]                    ");
	printf("\t -> Sair (apenas a partir do diretorio root)\n");
	
	// HD
	printf("\n-> Help menu HD\n");
	printf("\t listhd    [command]                    ");
	printf("\t -> Lista os HDs disponiveis\n");
	
	printf("\t selecthd  [command][nome_HD]           ");
	printf("\t -> Seleciona o HD desejado\n");
	
	printf("\t createhd  [command][nome_HD]           ");
	printf("\t -> Cria um HD com o nome especificado\n");
	
	printf("\t formathd  [command][nome_HD]           ");
	printf("\t -> formata o HD desejado\n");
	
	printf("\t typehd    [command][nome_HD]           ");
	printf("\t -> Mostra os blocos utilizados do HD\n");
	
	printf("\t removehd  [command][nome_HD]           ");
	printf("\t -> remove o HD selecionado\n");
	
	// ARQUIVOS
	printf("\n");
	printf("\n-> Help menu Arquivos (Apenas quando tem um HD ja selecionado)\n");
	printf("\t create    [command][nome_arquivo]           ");
	printf("\t -> Cria um arquivo com o nome especificado\n");
	
	printf("\t typehd    [command]                         ");
	printf("\t -> Mostra os blocos utilizados do HD\n");
	
	printf("\t dir       [command]                         ");
	printf("\t -> Mostra todos os arquivos do HD\n");
	
	printf("\t remove    [command][nome_arquivo]           ");
	printf("\t -> Remove o arquivo com o nome especificado\n");
	
	printf("\t type      [command][nome_arquivo]           ");
	printf("\t -> Mostra o conteudo do arquivo\n");
	
	printf("\t copy      [command][nome][novo_nome]        ");
	printf("\t -> Realiza uma copia do arquivo\n");
	
	printf("\t rename    [command][antigo_nome][novo_nome] ");
	printf("\t -> Renomeia o arquivo\n");
	
	printf("\t edit      [command][nome_arquivo]           ");
	printf("\t -> Edita o arquivo\n");
	
	printf("\t status    [command]                         ");
	printf("\t -> Status do HD selecionado\n");
	
	printf("\t # ou root [command]                         ");
	printf("\t -> Sai do HD selecionado\n\n");
	
	printf("\n");
}

int main() {
	SystemCore sysHdCore;
	
	string cmd, complementoTemp;
	char complemento[10];
	bool loop = true;
	
	printf("Grupo EPSILON, v2.0 (Centro universitario FEI) - @FelipeDantas, @FelipeLira\n\n");
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
		else if(cmd == "removehd"){
			sysHdCore.DelHd(complemento);
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
			
			sysHdCore.TypeHd(complemento, 0);
			
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
