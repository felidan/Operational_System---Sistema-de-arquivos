#include "SystemCore.h"

SystemCore::SystemCore(){
	nomeHd[0] = '*';
	PATH = "HDVirtual\\";//{"C:\\HDVirtual\\"};
}

void SystemCore::ListHd(){
	char buffer[30];
	
	strcpy(buffer,"dir /B ");
	int i;
	for(i = 0; i<PATH.length(); i++){
		buffer[(i+7)] = PATH[i];
	}
	buffer[(i+7)] = 0;
	
	printf("\n");
	system(buffer);
	printf("\n");
}

bool SystemCore::inicializarHd(char nome[]){
	FILE *fp;
	char caminho[100];
	int i;
	for(i = 0; i<PATH.length(); i++){
		caminho[i] = PATH[i];	
	}
	caminho[i] = 0;
	
	try{
		// adiciona a extens�o do HD
		strcpy(nomeHd, nome);
		strcat(nomeHd, ".flp");
		strcat(caminho, nomeHd);
		
		// Abre o HD
		if((fp = fopen(caminho, "rt")) == NULL){
			printf("\tErro na leitura do HD: %s\n", nome);
			nomeHd[0] = 0;
			return false;
		}	

	   printf("\n\tInicializando..\n");
	   
	   // buffer ira armazenar o HD em memoria
	   char buffer[(MAX_BLOCO_DIR + MAX_BLOCO_ARQ)][MAX_TAMANHO_BLOCO+1];
	   
	   // Posiciona o cursor no in�cio do arquivo
	   fseek(fp, 0, SEEK_SET);
		
	   // l� o HD e armazena no buffer
	   fread(buffer, MAX_TAMANHO_BLOCO + 1, MAX_BLOCO_DIR + MAX_BLOCO_ARQ, fp);
	   
	   // Carrega bloco de diret�rio
	   for(int i=0; i<MAX_BLOCO_DIR; i++){
	   		for(int j=0; j<MAX_TAMANHO_BLOCO; j++){
	   			blocoDiretorio[i][j] = buffer[i][j];
			}
	   }
	   
	   // Carrega bloco de arquivo
	   for(int i=0; i<MAX_BLOCO_ARQ; i++){
	   		for(int j=0; j<MAX_TAMANHO_BLOCO; j++){
	   			blocoArquivo[i][j] = buffer[(MAX_BLOCO_DIR + i)][j];
			}
	   }
	   
	   fclose(fp);
	   
	   printf("\tInicializacao concluida.\n\n");
	   return true;
	}
	catch(exception& e){
		cout<<"Exception: "<<e.what()<<endl;
		
		return false;
	}
}

bool SystemCore::CriarHd(char nome[]){
	FILE *fp;
	char caminho[30];
	int i;
	
	// monta o caminho do HD
	for(i = 0; i<PATH.length(); i++){
		caminho[i] = PATH[i];	
	}
	caminho[i] = 0;
	
	// adiciona a extens�o
	strcat(caminho, nome);
	strcat(caminho, ".flp");
	
	printf("\n\tCriado HD %s..\n", nome);
	
	// abre o HD	
	if((fp = fopen(caminho, "wt")) == NULL){
		cout<<"\tErro na criacao do HD"<<endl;
	}
	
	printf("\tFormatando HD..\n\n");
	
	// Formatando o HD criado...
	for(int i=0; i<(MAX_BLOCO_DIR + MAX_BLOCO_ARQ); i++){
		for(int j=0; j<MAX_TAMANHO_BLOCO; j++){
			fprintf(fp, "f");		
		}
		fprintf(fp, "\n");
	}

	fclose(fp);
	
	printf("\tHD criado com sucesso.\n\n");
	
	// depois de concluido a cria��o o HD ser� iniciado
	inicializarHd(nome);
}

bool SystemCore::FormatarHd(char nome[]){
	FILE *fp;
	char caminho[100];
	int confirm, i;
	
	// monta o caminho do HD
	for(i = 0; i<PATH.length(); i++){
		caminho[i] = PATH[i];	
	}
	caminho[i] = 0;
	
	// inclui a extens�o do arquivo
	strcat(caminho, nome);
	strcat(caminho, ".flp");
	
	try{
		printf("\n\tDeseja realmente formatar o HD %s? (1 = SIM, 0 = NAO) -> ", nome);
		scanf("%d%*c", &confirm);
		
		if(confirm == 1){
			printf("\n\tIniciando formatacao..\n");
			
			// Formata bloco de diretorio
			for(int i=0; i<MAX_BLOCO_DIR; i++){
				for(int j=0; j<MAX_TAMANHO_BLOCO; j++){
					blocoDiretorio[i][j] = 'f';
				}
			}
			
			// Formata bloco de arquivos
			for(int i=0; i<MAX_BLOCO_ARQ; i++){
				for(int j=0; j<MAX_TAMANHO_BLOCO; j++){
					blocoArquivo[i][j] = 'f';
				}
			}
			
			// Salva os dados que est�o em memoria para que o HD e a memoria fiquem alinhados
			Salvar(nome);
			
			printf("\tFormatacao concluida!\n\n");
		}
		else if(confirm == 0){
			printf("\tFormatacao cancelada!\n\n");
			return false;
		}
		else{
			printf("\tComando nao reconhecido\n\n");
			return false;
		}
		return true;
	}
	catch(exception& e){
		cout<<"Exception: "<<e.what()<<endl;
		
		return false;
	}
}

bool SystemCore::TypeHd(char nome[]){
	FILE *fp;
	char caminho[100], str[2];
	int i;
	Ascii asc;
	
	// monta o caminho do arquivo
	for(i = 0; i<PATH.length(); i++){
		caminho[i] = PATH[i];	
	}
	
	caminho[i] = 0;
	
	try{
		//inclui a extens�o do HD
		strcat(caminho, nome);
		strcat(caminho, ".flp");
		
		// Abre o HD
		// Neste caso, a leitura do HD � feita pois neste contexto a fun��o 
		// inicializa n�o foi chamada ainda, j� que n�o � necess�rio selecionar 
		// um HD (selecthd) para executar o comando typehd 
		if((fp = fopen(caminho, "rt")) == NULL){
			printf("\tErro na leitura do HD: %s\n", nome);
			return false;
		}	

	   printf("\n\tColetando dados..\n");
	   
	   char buffer[(MAX_BLOCO_DIR + MAX_BLOCO_ARQ)][MAX_TAMANHO_BLOCO+1];
	   
	   // Posiciona o cursor no in�cio do arquivo
	   fseek(fp, 0, SEEK_SET);
	
	   // L� o HD e armazena no buffer
	   fread(buffer, MAX_TAMANHO_BLOCO + 1, MAX_BLOCO_DIR + MAX_BLOCO_ARQ, fp);
	   
	   printf("\n\t-> bloco de diretorio\n");
	   // Carrega bloco de diret�rio
	   // O bloco de diretorios n�o � gravado em hexadecimal, 
	   // sendo assim, n�o � necess�rio converter
	   for(int i=0; i<MAX_BLOCO_DIR; i++){
	   	   // este processo � necess�rio, pois a cada 2 letras em hexa temos um caracter
		   str[0] = buffer[i][0];
		   str[1] = buffer[i][1];
	   	   str[2] = 0;
		   
		   // Neste caso n�o queremos imprimir blocos que n�o est�o sendo utilizados, 
		   // por este motivo a compara��o para ver se � ff
		   if(strcmp(str, "ff") != 0){
		       printf("\n");
			   cout<<"\t\tL ";
			   cout.width(4);   
			   cout<<i;
			   cout<<": ";
		   
			   for(int j=0; j<MAX_TAMANHO_BLOCO; j++){
					
					str[0] = buffer[i][j];
					str[1] = 0;
					
					// L� apenas se for diferente de |, 
					// j� que para o nosso HD o caracter '|' � NULL
					if(strcmp(str, "|") != 0){
						printf("%c ", str[0]);	
					}
				}
			}
	   }
	   
	   printf("\n\n\t-> bloco de arquivos\n");
	   // Carrega bloco de arquivo
	   for(int i=MAX_BLOCO_DIR; i<(MAX_BLOCO_ARQ + MAX_BLOCO_DIR); i++){
	   	   
	   	   // este processo � necess�rio, pois a cada 2 letras em hexa temos um caracter
	   	   str[0] = buffer[i][0];
		   str[1] = buffer[i][1];
	   	   str[2] = 0;
				
		   // Neste caso n�o queremos imprimir blocos que n�o est�o sendo utilizados, 
		   // por este motivo a compara��o para ver se � ff
		   if(strcmp(str, "ff") != 0){
		       printf("\n");
			   cout<<"\t\tL ";
			   cout.width(4);   
			   cout<<i;
			   cout<<": ";
		   }
		   
		    // este for � respons�vel por imprimir em hexadecimal, ou seja, apenas l� o que est� no HD
			for(int j=0; j<MAX_TAMANHO_BLOCO; j=j+2){
				// este processo � necess�rio, pois a cada 2 letras em hexa temos um caracter
				str[0] = buffer[i][j];
				str[1] = buffer[i][(j+1)];
				str[2] = 0;
				
				if(strcmp(str, "ff") != 0){
					printf("%s ", str);	
				}
			}
			
			// este processo � necess�rio, pois a cada 2 letras em hexa temos um caracter
			str[0] = buffer[i][0];
		    str[1] = buffer[i][1];
	   	    str[2] = 0;
				
		    if(strcmp(str, "ff") != 0){
		    	printf("\n\t\t        ");
		    }
		    
			// este for � respons�vel por imprimir em caracteres ASCII 
			// utilizando a classe ascii criada para qualquer tipo de convers�o
		    for(int j=0; j<MAX_TAMANHO_BLOCO; j=j+2){
				// este processo � necess�rio, pois a cada 2 letras em hexa temos um caracter
				str[0] = buffer[i][j];
				str[1] = buffer[i][(j+1)];
				str[2] = 0;
				
				if(strcmp(str, "ff") != 0){
					// o if abaixo � necess�rio, pois caso na hora da cria��o do arquivo 
					// o usuario tenha apertado o enter, por exemplo, a representa��o ir� ficar desposicionada.. 
					// Ent�o sempre que ouver um caracter especial sera printado ?
					if(strcmp(str, "00") > 0 && strcmp(str, "1f") < 0){
						printf("?  ");
					}
					else{
						printf("%c  ", asc.getHexaToCarc(str));		
					}				
				}
			}
	   }
	   
	   fclose(fp);
	   
	   printf("\n\n");
	   	
	   return true;
	}
	catch(exception& e){
		cout<<"Exception: "<<e.what()<<endl;
		
		return false;
	}
}

void SystemCore::Salvar(char nome[]){
	FILE *fp;
	char caminho[30];
	int i;
	
	// monta o caminho do arquivo
	for(i = 0; i<PATH.length(); i++){
		caminho[i] = PATH[i];	
	}
	caminho[i] = 0;
	
	// adiciona a extens�o do HD
	strcat(caminho, nome);
	strcat(caminho, ".flp");
	
	// abre o HD
	if((fp = fopen(caminho, "wt")) == NULL){
		cout<<"\tErro ao salvar no HD"<<endl;
	}
	
	// Salva bloco de diretorio que est� em mem�ria
	for(int i=0; i<MAX_BLOCO_DIR; i++){
		for(int j=0; j<MAX_TAMANHO_BLOCO; j++){
			fprintf(fp, "%c", blocoDiretorio[i][j]);
		}
		fprintf(fp, "\n");
	}
	
	// Salva bloco de arquivos que est� em mem�ria
	for(int i=0; i<MAX_BLOCO_ARQ; i++){
		for(int j=0; j<MAX_TAMANHO_BLOCO; j++){
			fprintf(fp, "%c", blocoArquivo[i][j]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
}

bool SystemCore::CriarArquivo(char nome[]){
	Ascii a;
	char c;
	char buffer[1000], bufferHexa[2000], nomeHdTemp[30];
	string temp;
	int i=0, j=0, posicaoDiretorio, posicaoArquivo, qtBlocosi;
	double qtBlocosf;
	
	// O if abaixo � necess�rio para que um arquivo ocupe apenas um bloco de diret�rio
	if(strlen(nome) > 26){
		printf("\n\tO nome do arquivo esta muito grande\n\tFavor informar um nome com o limite de 26 caracteres.\n\n");
		return false;
	}
	
	printf("\nDigite o conteudo do arquivo (ENTER e em seguida CTRL-Z para encerrar):\n");
	
	fflush(stdin);
	
	// L� os caracteres do arquivo digitados pelo usu�rio at� que seja precionado CTRL-Z
	while((c = getchar()) != EOF){
		buffer[i] = c;
		i++;
	}
	buffer[(i-1)] = 0;
	
	// Quantidade de blocos necess�rios para alocar o arquivo
	/*
	Como um caracter da tabela ASCII � representada por 2 caracteres que formam um em hexa, o buffer � multiplicado por 2
	Ou seja, se foi digitado 10 caracteres, quando este for convertido em hexa ser� necess�rio um bloco para armazenar 20.
	O +1 � devido ao caracter de fim do arquivo ('|') que ser� adicionado ao final para indicar que o arquivo acabou
	
	Este resultado � dividido pelo MAX_TAMANHO_BLOCO, para que se possa saber quantos blocos ser� necess�rio para armazenar o arquivo.
	Se, por exemplo, o resultado for 2.6 isso significar� que ser�o necess�rios 3 blocos seguidos na mem�ria para poder armazenar este arquivo
	*/
	qtBlocosf = (double)((strlen(buffer) * 2) + 1) / (double)MAX_TAMANHO_BLOCO;
	
	qtBlocosi = (int)qtBlocosf;
	
	if((qtBlocosf - qtBlocosi) > 0){
		qtBlocosi++;
	}
	
	// retorna a posi��o do primeiro bloco de diretorio dispon�vel
	posicaoDiretorio = FindBlocoDirVazio();
	
	// Procura a quantidade de blocos desejada e que estejam consecutivos na memoria e retorna o endere�o do primeiro bloco
	posicaoArquivo = FindBlocoArqVazio(qtBlocosi);
	
	// tratamento de espa�o
	if(posicaoDiretorio == -1){
		printf("\n\tNao ha espaco suficiente no bloco de diretorio para realizar esta operacao.\n\n");
		return false;
	}
	
	// tratamento de espa�o
	if(posicaoArquivo == -1){
		printf("\n\tNao ha espaco suficiente no bloco de arqiovos para realizar esta operacao.\n\n");
		return false;
	}
	
	// Inicializa o bloco a ser usado gravando | em todo o bloco
	for(int m=0; m<MAX_TAMANHO_BLOCO; m++){
		blocoDiretorio[posicaoDiretorio][m] = '|';
	}
	
	// Grava blocos de diretorios
	// tipo do arquivo (0)
	blocoDiretorio[posicaoDiretorio][0] = '0';
	
	// endere�o do inicio do arquivo
	char tempEndereco[4], tempP[4];
	
	// Converte o inteiro para char[]
	sprintf(tempP, "%d", (posicaoArquivo + MAX_BLOCO_DIR));
	
	for(int m=0; m<4; m++){
		tempEndereco[m]='0';
	}
	
	// Completa o endere�o com zero a esquerda para que possa ser gravado no bloco
	int k = 4;
	for(int m=strlen(tempP); m>=0; m--){
		tempEndereco[k]=tempP[m];
		k--;
	}
	
	// Grava endereco do inicio do arquivo
	k = 1;
	for(i=0; tempEndereco[i] != 0; i++){
		blocoDiretorio[posicaoDiretorio][k] = tempEndereco[i];
		k++;
	}
	
	// grava nome do arquivo
	k = 5;
	for(i=0; nome[i] != 0; i++){
		blocoDiretorio[posicaoDiretorio][k] = nome[i];
		k++;
	}
	
	// Grava blocos de arquivos
	k = 0;
	for(i=0; i<strlen(buffer); i++){
		// converte caracter em hexadecimal
		temp = a.getCaracToHexa(buffer[i]);
		
		blocoArquivo[posicaoArquivo][k] = temp[0];
		k++;
		blocoArquivo[posicaoArquivo][k] = temp[1];
		k++;
		
		if(k == MAX_TAMANHO_BLOCO){ // se chegou ao final do bloco..
			posicaoArquivo++; // passa para aproxima linha
			k = 0; // retorna para o primeiro byte
		}	
	}
	// grava fim do arquivo
	blocoArquivo[posicaoArquivo][k] = '7';
	blocoArquivo[posicaoArquivo][(k+1)] = 'c';
	
	// remove a extens�o do arquivo para possa ser pasado pra a fun��o de salvar
	strcpy(nomeHdTemp, this->nomeHd);
	nomeHdTemp[(strlen(nomeHdTemp)-4)] = 0; // remove o .flp
	
	// Salva HD
	Salvar(nomeHdTemp);
}	

bool SystemCore::RemoveArquivo(char nome[]){
	
	char tempEndereco[4], str[2], nomeHdTemp[30];
	int endereco, indice;
	
	// Procura o arquivo pelo nome
	indice = FindArquivoPorNome(nome);
	
	if(indice == -1){
		printf("\n\tArquivo nao encontrado.\n\n");
		return false;
	}
	
	// recupera o endere�o do inicio do arquivo para que o mesmo possa ser excluido
	for(int i=0; i<4; i++){
		tempEndereco[i] = blocoDiretorio[indice][(i+1)];
	}
	
	// Converte este endere�o para inteiro 
	endereco = atoi(tempEndereco);
	endereco = endereco - MAX_BLOCO_DIR;

	// apaga a parte de diretorio
	for(int i=0; i<MAX_TAMANHO_BLOCO; i++){
		blocoDiretorio[indice][i] = 'f';
	}
	
	// apaga a parte de arquivos
	for(int i=endereco; i<MAX_BLOCO_ARQ; i++){
		for(int j=0; j<MAX_TAMANHO_BLOCO; j=j+2){
				
			str[0] = blocoArquivo[i][j];
			str[1] = blocoArquivo[i][(j+1)];
			str[2] = 0;
			
			// apaga at� encontrar o caracter de fim de arquivo		
			if(strcmp(str, "7c") != 0){
				blocoArquivo[i][j] = 'f';
				blocoArquivo[i][(j+1)] = 'f';
			}
			else{
				// se foi encontrato o ultimo caracter ('|')...
				blocoArquivo[i][j] = 'f';
				blocoArquivo[i][(j+1)] = 'f';
				// encerra os dois fors
				j = MAX_TAMANHO_BLOCO;
				i = MAX_BLOCO_ARQ;
			}
		}
	}
	printf("\n\tArquivo %s removido.\n\n", nome);
	
	// remove a extens�o do nome do HD para que possa ser chamada a fun��o de salvar
	strcpy(nomeHdTemp, this->nomeHd);
	nomeHdTemp[(strlen(nomeHdTemp)-4)] = 0; // remove o .flp
	
	// Salva
	Salvar(nomeHdTemp);
	
	return true;
}

bool SystemCore::TypeArquivo(char nome[]){
	
	char tempEndereco[4], str[2];
	int endereco, indice;
	Ascii ascii;
	
	// Procura o arquivo pelo nome
	indice = FindArquivoPorNome(nome);
	
	if(indice == -1){
		printf("\n\tArquivo nao encontrado.\n\n");
		return false;
	}
	
	// recupera o endere�o do inicio do arquivo para que o mesmo possa ser excluido
	for(int i=0; i<4; i++){
		tempEndereco[i] = blocoDiretorio[indice][(i+1)];
	}
	
	// Converte este endere�o para inteiro 
	endereco = atoi(tempEndereco);
	endereco = endereco - MAX_BLOCO_DIR;

	printf("\ncaracteres:\n");
	// caracteres
	for(int i=endereco; i<MAX_BLOCO_ARQ; i++){
		for(int j=0; j<MAX_TAMANHO_BLOCO; j=j+2){
				
			str[0] = blocoArquivo[i][j];
			str[1] = blocoArquivo[i][(j+1)];
			str[2] = 0;
			// imprime at� ser diferente do caracter de fim de arquivo
			if(strcmp(str, "7c") != 0){
				printf("%c", ascii.getHexaToCarc(str));
			}
			else{ // Se encontrado o fim do arquivo, encerra os dois fors
				j = MAX_TAMANHO_BLOCO;
				i = MAX_BLOCO_ARQ;
			}
		}
	}
	
	printf("\n\nHexadecimal:\n");
	// hexa
	for(int i=endereco; i<MAX_BLOCO_ARQ; i++){
		for(int j=0; j<MAX_TAMANHO_BLOCO; j=j+2){
				
			str[0] = blocoArquivo[i][j];
			str[1] = blocoArquivo[i][(j+1)];
			str[2] = 0;
			// imprime at� ser diferente do caracter de fim de arquivo
			if(strcmp(str, "7c") != 0){
				printf("%s ", str);
			}
			else{ // Se encontrado o fim do arquivo, encerra os dois fors
				j = MAX_TAMANHO_BLOCO;
				i = MAX_BLOCO_ARQ;
			}
		}
	}
	
	printf("\n\n");
	
	return true;
}

int SystemCore::FindBlocoDirVazio(){
	
	char str[2];
	
	for(int i=0; i<MAX_BLOCO_DIR; i++){
		str[0] = blocoDiretorio[i][0];
		str[1] = blocoDiretorio[i][1];
		str[2] = 0;
		
		// se encontrou ff significa que o bloco est� vazio, ent�o retorna o endere�o
		if(strcmp(str, "ff") == 0){
			return i;
		}
	}
	
	return -1;
}

int SystemCore::FindBlocoArqVazio(int QtBloco){
	
	char str[2];
	int aux = 0;
	
	for(int i=0; i<MAX_BLOCO_ARQ; i++){
		str[0] = blocoArquivo[i][0];
		str[1] = blocoArquivo[i][1];
		str[2] = 0;
		// se encontrou um bloco vazio..
		if(strcmp(str, "ff") == 0){
			// soma um no contador
			aux++;
		}
		else{
			aux = 0;
		}
		// verifica se � a quantidade de blocos necessario
		if(aux == QtBloco){
			return (i - (aux-1));
		}
	}
	
	return -1;
}
	
int SystemCore::FindArquivoPorNome(char nome[]){
	
	char str[2], tempNome[27];
	
	for(int i=0; i<MAX_BLOCO_DIR; i++){
		str[0] = blocoDiretorio[i][0];
		str[1] = blocoDiretorio[i][1];
		str[2] = 0;
		// se n�o for um bloco vazio...
		if(strcmp(str, "ff") != 0){
			int k = 0;
			// recupera o nome do arquivo do bloco..
			for(int j=5; blocoDiretorio[i][j] != '|'; j++){
				tempNome[k] = blocoDiretorio[i][j];
				k++;
			}
			tempNome[k] = 0;
			// verifica se este � o bloco procurado
			if(strcmp(tempNome, nome) == 0){
				return i;
			}
		}
	}
	
	return -1;
}
	
SystemCore::~SystemCore(){
	
}
