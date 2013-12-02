// JA.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>

//valores Globais
#define SISTEMA_MAPA_MAX_CELULAS 11			//definicoes do sistema (mapas, ficheiros, etc)
#define SISTEMA_MAPA_MAX_DESCRICAO 1000
#define JOGADOR_ENERGIA 100					//definicoes do jogador
#define JOGADOR_ENERGIA_SU_MODE 1000
#define JOGADOR_MAX_NOME 20
#define JOGADOR_POSICAO_INICIAL 0
#define ADVERSARIO_ENERGIA 100				//definicoes do adversario
#define ADVERSARIO_POSICAO_INICIAL 1

/*
Estruturas do jogo:
=> C�lulas: ou salas do jogo
=> Jogador: nome, energia, posi��o, etc
=> Adversario: energia e posi��o
*/

struct Celula{
        int norte;
        int sul;
        int este;
        int oeste;
        int tesouro;
        char descricao[SISTEMA_MAPA_MAX_DESCRICAO]; //descreve a sala onde o jogador esta
};

struct Jogador{
	char jogadorNome[JOGADOR_MAX_NOME];
	int jogadorEnergia;
	int jogadorPosicao;
};

struct Adversario{
	int adversarioEnergia;
	int adversarioPosicao;
};


/*
Inicializa��o do Jogador e Advers�rio
*/
void iniciarJogador(struct Jogador *jogador){
        system("cls");
        printf("\n\t\t/\\ /\\ /\\");
        printf("\n\t\t## ## ##");
        printf("\n\t\t########");
        printf("\n\t\t### ####");
        printf("\n\t\t### ####");
        printf("\n\t\t########   /\\    /\\    /\\    /\\    /\\    /\\    /\\");
        printf("\n\t\t########   ##    ##    ##    ##    ##    ##    ##");
        printf("\n\t\t#################################################");
        printf("\n\t\t#################################################");
        printf("\n\t\t##################                  #############");
        printf("\n\t\t################## JOGO DE AVENTURA #############");
        printf("\n\t\t### ##############                  #############");
        printf("\n\t\t##   ############################################");
        printf("\n##################   ##########################################################");
        printf("\n###############################################################################");
        printf("\n\n");
        printf("Bem vindo Aventureiro.\nInsere o teu nome: ");
        scanf("%s", jogador->jogadorNome);
        jogador -> jogadorEnergia = JOGADOR_ENERGIA;
        jogador -> jogadorPosicao = JOGADOR_POSICAO_INICIAL;
        system("cls");
}

void iniciarAdversario(struct Adversario *adversario){
	adversario->adversarioEnergia = ADVERSARIO_ENERGIA;
	adversario->adversarioPosicao = ADVERSARIO_POSICAO_INICIAL;
}

void iniciarMapa(struct Celula mapa[]){
	/*				MAPA	
	 _____________________________________________
	|        |                  |           |     |
	|   0             1                2    |     |
	|___  ___|__________________|_____  ____|     |
	|        |                              |  3  |
	|   4                   5                     |
	|___  ___|_____________  _______________|     |
	|        |          |          |        |__  _|
	|   6    |     7    |   8      |   9    |     |
	|                                       |  10 |
	|________|__________|__________|________|_____|
	*/
	mapa[0].norte = -1;
	mapa[0].sul = 4;
	mapa[0].este = 1;
	mapa[0].oeste = -1;
	mapa[0].tesouro = 0;
	strcpy(mapa[0].descricao, "Sala 0");

	mapa[1].norte = -1;
	mapa[1].sul = -1;
	mapa[1].este = 2;
	mapa[1].oeste = 0;
	mapa[1].tesouro = 0;
	strcpy(mapa[1].descricao, "Sala 1");

	mapa[2].norte = -1;
	mapa[2].sul = 5;
	mapa[2].este = -1;
	mapa[2].oeste = 1;
	mapa[2].tesouro = 0;
	strcpy(mapa[2].descricao, "Sala 2");

	mapa[3].norte = -1;
	mapa[3].sul = 10;
	mapa[3].este = -1;
	mapa[3].oeste = 5;
	mapa[3].tesouro = 0;
	strcpy(mapa[3].descricao, "Sala 3");

	mapa[4].norte = 0;
	mapa[4].sul = 6;
	mapa[4].este = 5;
	mapa[4].oeste = -1;
	mapa[4].tesouro = 0;
	strcpy(mapa[4].descricao, "Sala 4");

	mapa[5].norte = 2;
	mapa[5].sul = 8;
	mapa[5].este = 3;
	mapa[5].oeste = 4;
	mapa[5].tesouro = 0;
	strcpy(mapa[5].descricao, "Sala 5");

	mapa[6].norte = 4;
	mapa[6].sul = -1;
	mapa[6].este = 7;
	mapa[6].oeste = -1;
	mapa[6].tesouro = 0;
	strcpy(mapa[6].descricao, "Sala 6");

	mapa[7].norte = -1;
	mapa[7].sul = -1;
	mapa[7].este = 8;
	mapa[7].oeste = 6;
	mapa[7].tesouro = 0;
	strcpy(mapa[7].descricao, "Sala 7");

	mapa[8].norte = 5;
	mapa[8].sul = -1;
	mapa[8].este = 9;
	mapa[8].oeste = 7;
	mapa[8].tesouro = 0;
	strcpy(mapa[8].descricao, "Sala 8");

	mapa[9].norte = -1;
	mapa[9].sul = -1;
	mapa[9].este = -1;
	mapa[9].oeste = 8;
	mapa[9].tesouro = 0;
	strcpy(mapa[9].descricao, "Sala 9");

	mapa[10].norte = 3;
	mapa[10].sul = -1;
	mapa[10].este = -1;
	mapa[10].oeste = -1;
	mapa[10].tesouro = 1;
	strcpy(mapa[10].descricao, "Sala 10");
}



/*
Fun��es "principais" do jogo
=> carregarTeclaParaContinuar(): fun��o para continuar o jogo ap�s carregar no ENTER (alternativa ao uso do system("pause"); )
=> combatePersonagens(): fun��o que simula o combate das personagens, escolhendo aleatoriamente o resultado final do combate independentemente da arma seleccionada
=> verificaFimJogo(): faz a verifica��o da energia das personagens. A que chegar primeiro a zero (0) perde
=> movimentarAdversario(): criar o movimento do adversario ao longo do mapa
=> definirLocalizacao(): guarda as posicoes no mapa lidas do ficheiro
=> abrirMapaTXT(): le o conteudo do mapa de um ficheiro txt
=> abrirMapaBIN(): le o conteudo do mapa de um ficheiro binario
=> salvarJogo(): guarda as posicoes e estados das personagens no jogo
*/

void carregarTeclaParaContinuar(){
	printf("Carrega ENTER para continuar...");
	char c = getchar();
}

void combatePersonagens(struct Jogador *jogador, struct Adversario *adversario){
	char opcaoArma[2];
	int adversarioDefendeOuAtaca = 0; //escolhe entre as personagens a qual deve levar os danos: adversario(0) ou jogador(1)
	int faca = 5;
	int pedra = 10;
	int magia = 15;
	//int armaAleatoria = 0;

	//armaAleatoria = rand() % 3;

	if( jogador->jogadorPosicao == adversario->adversarioPosicao ){
		system("cls");
		printf("\nEncontras-te o monstro!! Prepara-te para a luta!\n\nEscolhe a arma:");
		printf("\n1. Faca\n2. Pedra\n3. Magia");
		printf("\n\nSeleciona uma op��o: ");
		scanf("%s", opcaoArma);

		if( strcmp(opcaoArma,"1") == 0 ){
			adversarioDefendeOuAtaca = rand() % 3;

			//Ponto 1: o jogador acerta no adversario
			if( adversarioDefendeOuAtaca == 0 ){
				adversario->adversarioEnergia -= faca;
				printf("\n\nConseguis-te acertar no advers�rio! O advers�rio perdeu %d pontos de energia e fugiu.\n\n\n\n", faca);
				system("pause");
				//carregarTeclaParaContinuar();
			}
			//Ponto 2: o adversario acerta no jogador
			if( adversarioDefendeOuAtaca == 1 ){
				jogador->jogadorEnergia -= faca;
				printf("\n\nO advers�rio defendeu-se e atacou logo em seguida. N�o conseguis-te defender,\npor isso sofres-te %d pontos de energia.\n\n\n\n", faca);
				system("pause");
				//carregarTeclaParaContinuar();
			}
			//Ponto 3: o adversario e o jogador falham os ataques
			if( adversarioDefendeOuAtaca == 2 ){
				printf("\n\nO advers�rio conseguiu defender o teu ataque, mas fugiu. Vamos continuar!\n\n\n\n");
				system("pause");
				//carregarTeclaParaContinuar();
			}
		}

		if( strcmp(opcaoArma,"2") == 0 ){
			adversarioDefendeOuAtaca = rand() % 3;

			//Ponto 1: o jogador acerta no adversario
			if( adversarioDefendeOuAtaca == 0 ){
				adversario->adversarioEnergia -= pedra;
				printf("\n\nConseguis-te acertar no advers�rio! O advers�rio perdeu %d pontos de energia e fugiu.\n\n\n\n", pedra);
				system("pause");
				//carregarTeclaParaContinuar();
			}
			//Ponto 2: o adversario acerta no jogador
			if( adversarioDefendeOuAtaca == 1 ){
				jogador->jogadorEnergia -= pedra;
				printf("\n\nO advers�rio defendeu-se e atacou logo em seguida. N�o conseguis-te defender,\npor isso sofres-te %d pontos de energia.\n\n\n\n", pedra);
				system("pause");
				//carregarTeclaParaContinuar();
			}
			//Ponto 3: o adversario e o jogador falham os ataques
			if( adversarioDefendeOuAtaca == 2 ){
				printf("\n\nO advers�rio conseguiu defender o teu ataque, mas fugiu. Vamos continuar!\n\n\n\n");
				system("pause");
				//carregarTeclaParaContinuar();
			}
		}

		if( strcmp(opcaoArma,"3") == 0 ){
			adversarioDefendeOuAtaca = rand() % 3;

			//Ponto 1: o jogador acerta no adversario
			if( adversarioDefendeOuAtaca == 0 ){
				adversario->adversarioEnergia -= magia;
				printf("\n\nConseguis-te acertar no advers�rio! O advers�rio perdeu %d pontos de energia e fugiu.\n\n\n\n", magia);
				system("pause");
				//carregarTeclaParaContinuar();
			}
			//Ponto 2: o adversario acerta no jogador
			if( adversarioDefendeOuAtaca == 1 ){
				jogador->jogadorEnergia -= magia;
				printf("\n\nO advers�rio defendeu-se e atacou logo em seguida. N�o conseguis-te defender,\npor isso sofres-te %d pontos de energia.\n\n\n\n", magia);
				system("pause");
				//carregarTeclaParaContinuar();
			}
			//Ponto 3: o adversario e o jogador falham os ataques
			if( adversarioDefendeOuAtaca == 2 ){
				printf("\n\nO advers�rio conseguiu defender o teu ataque, mas fugiu. Vamos continuar!\n\n\n\n");
				system("pause");
				//carregarTeclaParaContinuar();
			}
		}


	}

}

void verificaFimJogo(struct Jogador *jogador, struct Adversario *adversario){
	if( adversario->adversarioEnergia <= 0 ){
		system("cls");
		printf("\n\t\t/\\ /\\ /\\");
        printf("\n\t\t## ## ##");
        printf("\n\t\t########");
        printf("\n\t\t### ####");
        printf("\n\t\t### ####");
        printf("\n\t\t########   /\\    /\\    /\\    /\\    /\\    /\\    /\\");
        printf("\n\t\t########   ##    ##    ##    ##    ##    ##    ##");
        printf("\n\t\t#################################################");
        printf("\n\t\t#################################################");
        printf("\n\t\t##################                  #############");
        printf("\n\t\t################## JOGO DE AVENTURA #############");
        printf("\n\t\t### ##############                  #############");
        printf("\n\t\t##   ############################################");
        printf("\n##################   ##########################################################");
        printf("\n###############################################################################");
        printf("\n\n");
        printf("Parab�ns %s vences-te o advers�rio, no entanto esqueces-te do tesouro.\nTenta novamente.", jogador->jogadorNome);
        printf("\n\n\n");
        system("pause");
		//carregarTeclaParaContinuar();
    }

	if( jogador->jogadorEnergia <= 0 ){
		system("cls");
		printf("\n\t\t/\\ /\\ /\\");
        printf("\n\t\t## ## ##");
        printf("\n\t\t########");
        printf("\n\t\t### ####");
        printf("\n\t\t### ####");
        printf("\n\t\t########   /\\    /\\    /\\    /\\    /\\    /\\    /\\");
        printf("\n\t\t########   ##    ##    ##    ##    ##    ##    ##");
        printf("\n\t\t#################################################");
        printf("\n\t\t#################################################");
        printf("\n\t\t##################                  #############");
        printf("\n\t\t################## JOGO DE AVENTURA #############");
        printf("\n\t\t### ##############                  #############");
        printf("\n\t\t##   ############################################");
        printf("\n##################   ##########################################################");
        printf("\n###############################################################################");
        printf("\n\n");
        printf("%s o monstro venceu-te! Descansa e tenta mais tarde...", jogador->jogadorNome);
        printf("\n\n\n");
        system("pause");
		//carregarTeclaParaContinuar();
    }
}

void movimentarAdversario(struct Adversario *adversario){
	int movimentarAdversario = 10; //permite movimentar o adversario no mapa

	movimentarAdversario = rand() % 10; //determina a sala onde o adversario ira aparecer
	adversario->adversarioPosicao = movimentarAdversario; //movimenta o adversario para a casa escolhida aleatoriamente na linha de cima
}

void definirLocalizacao(struct Celula *mapa, int norte, int sul, int este, int oeste, int tesouro, char *desc){
	mapa->norte = norte;
	mapa->sul = sul;
	mapa->este = este;
	mapa->oeste = oeste;
	mapa->tesouro = tesouro;
	strcpy(mapa->descricao, desc);
}

void abrirMapaTXT(struct Celula mapa[]){
	FILE *file;
	char linha[SISTEMA_MAPA_MAX_DESCRICAO];
	struct Celula mapaTemporario;
	int c = 0;

	file = fopen("..\\Debug\\data\\mapa.txt", "r");

	while( fgets(linha, SISTEMA_MAPA_MAX_DESCRICAO, file) != NULL){
		if( strcmp(linha, "\n") == 0 ){
			definirLocalizacao(mapa++, mapaTemporario.norte, mapaTemporario.sul, mapaTemporario.este, mapaTemporario.oeste, mapaTemporario.tesouro, mapaTemporario.descricao);
			c = 0;
		}else{
			switch(c){
			case 0:
				mapaTemporario.norte = atoi(linha);
				break;
			case 1:
				mapaTemporario.sul = atoi(linha);
				break;
			case 2:
				mapaTemporario.este = atoi(linha);
				break;
			case 3:
				mapaTemporario.oeste = atoi(linha);
				break;
			case 4:
				mapaTemporario.tesouro = atoi(linha);
				break;
			case 5:
				strcpy(mapaTemporario.descricao, linha);
				break;
			}
			c++;
		}
	}
	
	definirLocalizacao(mapa++, mapaTemporario.norte, mapaTemporario.sul, mapaTemporario.este, mapaTemporario.oeste, mapaTemporario.tesouro, mapaTemporario.descricao);
	fclose(file);
}

//FAZER ESTA FUNCAO!!
void abrirMapaBIN(struct Celula mapa[]){
	//
}

void salvarJogoTXT(struct Jogador *jogador, struct Adversario *adversario){
	FILE *f;

	f = fopen("..\\Debug\\data\\saveGame.txt","w");

	if (f != NULL){
		fprintf(f, "%s\n", jogador->jogadorNome);
		fprintf(f, "%d\n", jogador->jogadorEnergia);
		fprintf(f, "%d\n", jogador->jogadorPosicao);
		fprintf(f, "%d\n", adversario->adversarioEnergia);
		fprintf(f, "%d\n", adversario->adversarioPosicao);
	}

	fclose(f);
}

void salvarJogoBIN(struct Jogador *jogador, struct Adversario *adversario){
	FILE *f;
	int i = 1;

	f = fopen("..\\Debug\\data\\saveGame.bin","wb");

	if (f != NULL){

		fwrite(jogador, sizeof(struct Jogador), 1, f);
		fwrite(adversario, sizeof(struct Adversario), 1, f);

		/*fprintf(f, "%s\n", jogador->jogadorNome);
		fprintf(f, "%d\n", jogador->jogadorEnergia);
		fprintf(f, "%d\n", jogador->jogadorPosicao);
		fprintf(f, "%d\n", adversario->adversarioEnergia);
		fprintf(f, "%d\n", adversario->adversarioPosicao);*/
	}

	fclose(f);
}

int carregarJogoBin(struct Jogador *jogador, struct Adversario *adversario)
{
  FILE *f;

  f = fopen("..\\Debug\\data\\saveGame.bin","rb");

  if (f != NULL){
	fread(jogador, sizeof(struct Jogador), 1, f);
	fread(adversario, sizeof(struct Adversario), 1, f);
  }

  fclose(f);
  return 0;
}



/*
As fun��es abaixo realizam o aspeto grafico do jogo
=> graficoJogoCorrenteBanner(): insere o banner com informacao do nome/energia do jogador no decorrer do jogo
=> grafioMenuIntro(): Mostra o ecr� de boas vindas ao jogo
=> graficoMenuMenuPrincipal(): Cria o Menu Principal com as op��es novo jogo, carregar, sair...
=> graficoJogoTesouroEncontrado(): Se o jogador encontrar o tesouro mostra o ecra informativo
=> graficoMenuCreditosFinais(): Mostra o ecra com os creditos: autor, data...
*/
void graficoJogoCorrenteBanner(struct Jogador *jogador, struct Adversario *adversario){
	//Banner que aparece durante o jogo a informar os dados do jogador
	system("cls");
	printf("     Nome: %s  |  Energia: %d\n" , jogador->jogadorNome, jogador->jogadorEnergia);
	//printf( "  Energia: %d  | Energia (Advers�rio): %d \n" , jogador->jogadorEnergia, adversario->adversarioEnergia);
	printf("Posicao jogador %d = adversario %d = tesouro = 10\n", jogador->jogadorPosicao, adversario->adversarioPosicao);
	printf( "-------------------------------------------------------------------------------\n\n" );
}

void graficoMenuIntro(){ //Primeiro Imagem que aparece assim que o jogo inicia
    system("cls");
    printf("\n\t\t/\\ /\\ /\\");
    printf("\n\t\t## ## ##");
    printf("\n\t\t########");
    printf("\n\t\t### ####");
    printf("\n\t\t### ####");
    printf("\n\t\t########   /\\    /\\    /\\    /\\    /\\    /\\    /\\");
    printf("\n\t\t########   ##    ##    ##    ##    ##    ##    ##");
    printf("\n\t\t#################################################");
    printf("\n\t\t#################################################");
    printf("\n\t\t##################                  #############");
    printf("\n\t\t################## JOGO DE AVENTURA #############");
    printf("\n\t\t### ##############                  #############");
    printf("\n\t\t##   ############################################");
    printf("\n\t\t##   ############################################");
    printf("\n\n\n");
    system("pause");
	//carregarTeclaParaContinuar();
}

void graficoMenuMenuPrincipal(){
	//MENU Principal do jogo
    system("cls");
    printf("\n## ## ##");
    printf("\n## ## ##");
    printf("\n########");
    printf("\n### ####");
    printf("\n### ####");
    printf("\n########");
    printf("\n########   ##    ##    ##    ##    ##    ##    ##    ##    ##    ##");
    printf("\n########   ##    ##    ##    ##    ##    ##    ##    ##    ##    ##");
    printf("\n###################################################################");
    printf("\n###################################################################");
    printf("\n##################            JOGO DE AVENTURA          ###########");
    printf("\n##################                                      ###########");
    printf("\n##################   1. Novo Jogo                       ###########");
    printf("\n##################   2. Continuar Jogo                  ###########");
    printf("\n##################                                      ###########");
    printf("\n### ##############   9. Sair                            ###########");
    printf("\n##   #############                                      ###########");
    printf("\n##   ##############################################################");
    printf("\n\n\n");
}

void graficoJogoTesouroEncontrado(){
		system("cls");
		printf("\n\t\t/\\ /\\ /\\");
        printf("\n\t\t## ## ##");
        printf("\n\t\t########");
        printf("\n\t\t### ####");
        printf("\n\t\t### ####");
        printf("\n\t\t########   /\\    /\\    /\\    /\\    /\\    /\\    /\\");
        printf("\n\t\t########   ##    ##    ##    ##    ##    ##    ##");
        printf("\n\t\t#################################################");
        printf("\n\t\t#################################################");
        printf("\n\t\t##################                  #############");
        printf("\n\t\t################## JOGO DE AVENTURA #############");
        printf("\n\t\t### ##############                  #############");
        printf("\n\t\t##   ############################################");
        printf("\n##################   ##########################################################");
        printf("\n###############################################################################");
        printf("\n\n");
        printf("Parab�ns conseguis-te encontrar o tesouro!.");
        printf("\n\n\n");
        system("pause");
		//carregarTeclaParaContinuar();
}

void graficoMenuCreditosFinais(){
	//MENU que aparece no final do jogo
    system("cls");
    printf("\t\n\n\n/\\ /\\ /\\");
    printf("\t\n## ## ##");
    printf("\t\n## ## ##");
    printf("\t\n########");
    printf("\t\n########");
    printf("\t\n### ####");
    printf("\t\n### ####");
    printf("\t\n########   /\\    /\\    /\\    /\\    /\\    /\\    /\\    /\\    /\\    /\\");
    printf("\t\n########   ##    ##    ##    ##    ##    ##    ##    ##    ##    ##");
    printf("\t\n###################################################################");
    printf("\t\n###################################################################");
    printf("\t\n##################            JOGO DE AVENTURA          ###########");
    printf("\t\n##################                                      ###########");
    printf("\t\n##################   Desenvolvido por:                  ###########");
    printf("\t\n##################     Miguel Rosa, 6219                ###########");
    printf("\t\n##################     Disciplina: Sistemas Operativos  ###########");
    printf("\t\n### ##############     ESTiG, Novembro 2013             ###########");
    printf("\t\n##   #############                                      ###########");
    printf("\t\n##   ##############################################################");
    printf("\n\n\n");
}



int main(int argc, char* argv[])
{
	struct Jogador jogador;
	struct Adversario adversario;
	struct Celula mapa[SISTEMA_MAPA_MAX_CELULAS];
	char movimento[4];
	int movimentarTesouro = 10;
	setlocale(LC_ALL, "Portuguese");

	graficoMenuIntro();
	//verifica se o jogo foi executado em modo "super User"
    if( (argc == 2) && (strcmp(argv[1],"su") == 0) ){
		jogador.jogadorEnergia = JOGADOR_ENERGIA_SU_MODE;
    }

	//menu inicial
    graficoMenuMenuPrincipal();
    printf("Insira a op��o: ");
	scanf("%s", movimento);

	if ( strcmp(movimento, "1") == 0 ){ //novo jogo
		iniciarJogador(&jogador);
		iniciarAdversario(&adversario);
	}

	if ( strcmp(movimento, "2") == 0 ){ //carregar jogo
		carregarJogoBin(&jogador, &adversario);
	}

	//iniciarMapa(mapa);
	abrirMapaTXT(mapa);
	//abrirMapaBIN(mapa);


	//Inicio do Jogo
	while(true){
		graficoJogoCorrenteBanner(&jogador, &adversario);
		printf( "\n%s" , mapa[jogador.jogadorPosicao].descricao);
		printf( "\n\nPara onde queres ir?\n1. Norte\n2. Sul\n3. Este\n4. Oeste\n\n8. Guardar Jogo\n9. Sair do jogo\n\nQual � a op��o: ");
		scanf( "%s" , movimento);

		//movimento do jogador
		if ( ( strcmp( movimento, "1" ) == 0 ) && ( mapa[jogador.jogadorPosicao].norte != -1 )  ){
			jogador.jogadorPosicao = mapa[jogador.jogadorPosicao].norte;                
		}
		if ( ( strcmp( movimento, "2" ) == 0 ) && ( mapa[jogador.jogadorPosicao].sul != -1 ) ){
			jogador.jogadorPosicao = mapa[jogador.jogadorPosicao].sul;
		}
		if ( ( strcmp( movimento, "3" ) == 0 ) && ( mapa[jogador.jogadorPosicao].este != -1 )  ){
			jogador.jogadorPosicao = mapa[jogador.jogadorPosicao].este;
		}
		if ( ( strcmp( movimento, "4" ) == 0 ) && ( mapa[jogador.jogadorPosicao].oeste != -1 )  ){
			jogador.jogadorPosicao = mapa[jogador.jogadorPosicao].oeste;
		}
		if ( strcmp( movimento, "8" ) == 0  ){
			system("cls");
			printf("Jogo Guardado...\n\n");
			salvarJogoTXT(&jogador, &adversario);
			salvarJogoBIN(&jogador, &adversario);
			system("pause");
			//carregarTeclaParaContinuar();
		}
		if ( strcmp( movimento, "9" ) == 0  ){
			break; //termina o jogo e mostra a mensagem com info sobre o autor, disciplina, etc
		}

		//verifica se o jogador encontrou o tesouro
		if( jogador.jogadorPosicao == movimentarTesouro ){
			graficoJogoTesouroEncontrado();
			break;
		}

		//movimenta o adversario
		movimentarAdversario(&adversario);

		combatePersonagens(&jogador, &adversario);
		verificaFimJogo(&jogador, &adversario);
		system( "cls" );
	}

	graficoMenuCreditosFinais();
	system("pause");
	//carregarTeclaParaContinuar();
	return 0;
}