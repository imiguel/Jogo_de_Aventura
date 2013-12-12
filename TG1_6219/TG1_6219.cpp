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
#define JOGADOR_ENERGIA_SU_MODE 10000
#define JOGADOR_MAX_NOME 20
#define JOGADOR_POSICAO_INICIAL 0
#define ADVERSARIO_ENERGIA 100				//definicoes do adversario
#define ADVERSARIO_POSICAO_INICIAL 10
#define EMPTY _T( ' ' )


/*
Estruturas do jogo:
=> Células: ou salas do jogo
=> Jogador: nome, energia, posição, etc
=> Adversario: energia e posição
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
Inicialização das estruturas
=> LimparEcra(): Função para limpar o ecra que substitui o "system("pause");
=> iniciarJogador(): Inicializa a estrutura do jogador, recolhendo o nome e dá a energia à personagem
=> iniciarAdversario(): Inicializa a estrutura do adversário, colocando-o numa sala e dá a energia ao mesmo
=> iniciarMapa(): Inicializa a estrutura do mapa (mapa definido à mão)
*/
void limparEcra(){
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO strConsoleInfo;
	
	GetConsoleScreenBufferInfo( hStdout, &strConsoleInfo );
	
	COORD Home = {0, 0 };
	DWORD hWrittenChars;
	
	/*limpa os caracteres*/
	FillConsoleOutputCharacter( hStdout, EMPTY, strConsoleInfo.dwSize.X * strConsoleInfo.dwSize.Y, 
		Home, &hWrittenChars );
	/*limpa a formatação*/
	FillConsoleOutputAttribute( hStdout, strConsoleInfo.wAttributes, 
		strConsoleInfo.dwSize.X * strConsoleInfo.dwSize.Y, Home, &hWrittenChars );
	
	SetConsoleCursorPosition( hStdout, Home );
}

void iniciarJogador(struct Jogador *jogador){
		limparEcra();

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

		limparEcra();
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
	strcpy(mapa[0].descricao, "Entras-te no Castelo. O hall é amplo, há muito pó, vestigios de pegadas de outros exploradores. Há duas portas por abrir.");

	mapa[1].norte = -1;
	mapa[1].sul = -1;
	mapa[1].este = 2;
	mapa[1].oeste = 0;
	mapa[1].tesouro = 0;
	strcpy(mapa[1].descricao, "Escolheste a porta à direita e entras-te na Biblioteca. Há muito pó, e bastantes teias de aranha. O ar está "pesado" e sombrio.");

	mapa[2].norte = -1;
	mapa[2].sul = 5;
	mapa[2].este = -1;
	mapa[2].oeste = 1;
	mapa[2].tesouro = 0;
	strcpy(mapa[2].descricao, "Local menos próprio de todo o castelo... Por incrivel que pareça, estás no WC! Vontade para uma pausa?");

	mapa[3].norte = -1;
	mapa[3].sul = 10;
	mapa[3].este = -1;
	mapa[3].oeste = 5;
	mapa[3].tesouro = 0;
	strcpy(mapa[3].descricao, "Esta é a cozinha do castelo. É aqui que se costumavam fazer os grandes banquetes para a familia do Lord Greg.");

	mapa[4].norte = 0;
	mapa[4].sul = 6;
	mapa[4].este = 5;
	mapa[4].oeste = -1;
	mapa[4].tesouro = 0;
	strcpy(mapa[4].descricao, "Pequenina sala de espera. Embora o local seja apertado, é bastante acolhedor, com bastante luz natural.");

	mapa[5].norte = 2;
	mapa[5].sul = 8;
	mapa[5].este = 3;
	mapa[5].oeste = 4;
	mapa[5].tesouro = 0;
	strcpy(mapa[5].descricao, "Enorme salão. Aqui certamente se faziam as festas da família... Mas ao ver tudo arrumado deduz-se que raramente era utilizado!");

	mapa[6].norte = 4;
	mapa[6].sul = -1;
	mapa[6].este = 7;
	mapa[6].oeste = -1;
	mapa[6].tesouro = 0;
	strcpy(mapa[6].descricao, "Sala de canto era uma sala proibida... Lorg Greg usava-a como desculpa de estar amaldiçoada para poder dar algum espaço ao seu feiticeiro para trabalhar.");

	mapa[7].norte = -1;
	mapa[7].sul = -1;
	mapa[7].este = 8;
	mapa[7].oeste = 6;
	mapa[7].tesouro = 0;
	strcpy(mapa[7].descricao, "Pequeno terraço, pois a unica coisa que resta é uma estreita passagem junto à muralha do castelo...");

	mapa[8].norte = 5;
	mapa[8].sul = -1;
	mapa[8].este = 9;
	mapa[8].oeste = 7;
	mapa[8].tesouro = 0;
	strcpy(mapa[8].descricao, "Quarto dos filhos de Lorg Greg. Tal como o quarto do Lord Greg, este tambem estava muito danificado... Luta ou apenas a passagem do tempo?");

	mapa[9].norte = -1;
	mapa[9].sul = -1;
	mapa[9].este = -1;
	mapa[9].oeste = 8;
	mapa[9].tesouro = 0;
	strcpy(mapa[9].descricao, "Quarto do Lorg Greg. Soalho arrancado, janelas partidas... Acho que alguem andou aqui à luta... Ou seria o Log Greg a defender-se do monstro?");

	mapa[10].norte = 3;
	mapa[10].sul = -1;
	mapa[10].este = -1;
	mapa[10].oeste = -1;
	mapa[10].tesouro = 1;
	strcpy(mapa[10].descricao, "Chegas-te a uma sala fechada e sem luz. Jogas-te a mão ao bolso e tiras-te um isqueiro para poderes ter alguma luz.");
}



/*
Funções "principais" do jogo
=> carregarTeclaParaContinuar(): função para continuar o jogo após carregar no ENTER (alternativa ao uso do system("pause"); )
=> combatePersonagens(): função que simula o combate das personagens, escolhendo aleatoriamente o resultado final do combate independentemente da arma seleccionada
=> verificaFimJogo(): faz a verificação da energia das personagens. A que chegar primeiro a zero (0) perde
=> movimentarAdversario(): criar o movimento do adversario ao longo do mapa
=> definirLocalizacao(): guarda as posicoes no mapa lidas do ficheiro
=> abrirMapaTXT(): le o conteudo do mapa de um ficheiro txt
=> abrirMapaBIN(): le o conteudo do mapa de um ficheiro binario
=> salvarJogo(): guarda as posicoes e estados das personagens no jogo
*/

void carregarTeclaParaContinuar(){
	printf("Carrega ENTER para continuar...");
	char c = getchar();
	c = getchar();
}

void combatePersonagens(struct Jogador *jogador, struct Adversario *adversario){
	char opcaoArma[2];
	int adversarioDefendeOuAtaca = 0; //escolhe entre as personagens a qual deve levar os danos: adversario(0) ou jogador(1)
	int faca = 5;
	int pedra = 10;
	int magia = 15;

	if( jogador->jogadorPosicao == adversario->adversarioPosicao ){
		limparEcra();
		printf("\nEncontras-te o monstro!! Prepara-te para a luta!\n\nEscolhe a arma:");
		printf("\n1. Faca\n2. Pedra\n3. Magia");
		printf("\n\nSeleciona uma opção: ");
		scanf("%s", opcaoArma);

		if( strcmp(opcaoArma,"1") == 0 ){
			adversarioDefendeOuAtaca = rand() % 3;

			//Ponto 1: o jogador acerta no adversario
			if( adversarioDefendeOuAtaca == 0 ){
				adversario->adversarioEnergia -= faca;
				printf("\n\nConseguis-te acertar no adversário! O adversário perdeu %d pontos de energia e fugiu.\n\n\n\n", faca);
				carregarTeclaParaContinuar();
			}
			//Ponto 2: o adversario acerta no jogador
			if( adversarioDefendeOuAtaca == 1 ){
				jogador->jogadorEnergia -= faca;
				printf("\n\nO adversário defendeu-se e atacou logo em seguida. Não conseguis-te defender,\npor isso sofres-te %d pontos de energia.\n\n\n\n", faca);
				carregarTeclaParaContinuar();
			}
			//Ponto 3: o adversario e o jogador falham os ataques
			if( adversarioDefendeOuAtaca == 2 ){
				printf("\n\nO adversário conseguiu defender o teu ataque, mas fugiu. Vamos continuar!\n\n\n\n");
				carregarTeclaParaContinuar();
			}
		}

		if( strcmp(opcaoArma,"2") == 0 ){
			adversarioDefendeOuAtaca = rand() % 3;

			//Ponto 1: o jogador acerta no adversario
			if( adversarioDefendeOuAtaca == 0 ){
				adversario->adversarioEnergia -= pedra;
				printf("\n\nConseguis-te acertar no adversário! O adversário perdeu %d pontos de energia e fugiu.\n\n\n\n", pedra);
				carregarTeclaParaContinuar();
			}
			//Ponto 2: o adversario acerta no jogador
			if( adversarioDefendeOuAtaca == 1 ){
				jogador->jogadorEnergia -= pedra;
				printf("\n\nO adversário defendeu-se e atacou logo em seguida. Não conseguis-te defender,\npor isso sofres-te %d pontos de energia.\n\n\n\n", pedra);
				carregarTeclaParaContinuar();
			}
			//Ponto 3: o adversario e o jogador falham os ataques
			if( adversarioDefendeOuAtaca == 2 ){
				printf("\n\nO adversário conseguiu defender o teu ataque, mas fugiu. Vamos continuar!\n\n\n\n");
				carregarTeclaParaContinuar();
			}
		}

		if( strcmp(opcaoArma,"3") == 0 ){
			adversarioDefendeOuAtaca = rand() % 3;

			//Ponto 1: o jogador acerta no adversario
			if( adversarioDefendeOuAtaca == 0 ){
				adversario->adversarioEnergia -= magia;
				printf("\n\nConseguis-te acertar no adversário! O adversário perdeu %d pontos de energia e fugiu.\n\n\n\n", magia);
				carregarTeclaParaContinuar();
			}
			//Ponto 2: o adversario acerta no jogador
			if( adversarioDefendeOuAtaca == 1 ){
				jogador->jogadorEnergia -= magia;
				printf("\n\nO adversário defendeu-se e atacou logo em seguida. Não conseguis-te defender,\npor isso sofres-te %d pontos de energia.\n\n\n\n", magia);
				carregarTeclaParaContinuar();
			}
			//Ponto 3: o adversario e o jogador falham os ataques
			if( adversarioDefendeOuAtaca == 2 ){
				printf("\n\nO adversário conseguiu defender o teu ataque, mas fugiu. Vamos continuar!\n\n\n\n");
				carregarTeclaParaContinuar();
			}
		}


	}

}

void verificaFimJogo(struct Jogador *jogador, struct Adversario *adversario){
	if( adversario->adversarioEnergia <= 0 ){
		limparEcra();
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
        printf("Parabéns %s vences-te o adversário, no entanto esqueces-te do tesouro.\nTenta novamente.", jogador->jogadorNome);
        printf("\n\n\n");
        //system("pause");
		carregarTeclaParaContinuar();
    }

	if( jogador->jogadorEnergia <= 0 ){
		limparEcra();
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
		carregarTeclaParaContinuar();
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
As funções abaixo realizam o aspeto grafico do jogo
=> graficoJogoCorrenteBanner(): insere o banner com informacao do nome/energia do jogador no decorrer do jogo
=> grafioMenuIntro(): Mostra o ecrã de boas vindas ao jogo
=> graficoMenuMenuPrincipal(): Cria o Menu Principal com as opções novo jogo, carregar, sair...
=> graficoJogoTesouroEncontrado(): Se o jogador encontrar o tesouro mostra o ecra informativo
=> graficoMenuCreditosFinais(): Mostra o ecra com os creditos: autor, data...
*/
void graficoJogoCorrenteBanner(struct Jogador *jogador, struct Adversario *adversario){
	//Banner que aparece durante o jogo a informar os dados do jogador
	limparEcra();

	printf("\n\t\t##  Nome: %s  |  Energia: %d\n" , jogador->jogadorNome, jogador->jogadorEnergia);
	printf( "-------------------------------------------------------------------------------\n\n" );
}

void graficoMenuIntro(){ //Primeiro Imagem que aparece assim que o jogo inicia
	limparEcra();

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

	carregarTeclaParaContinuar();
}

void graficoMenuMenuPrincipal(){
	//MENU Principal do jogo
    limparEcra();

    printf("\n/\\ /\\ /\\");
    printf("\n## ## ##");
    printf("\n########");
    printf("\n### ####");
    printf("\n### ####");
    printf("\n########");
    printf("\n########   /\\    /\\    /\\    /\\    /\\    /\\    /\\    /\\    /\\    /\\");
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
	limparEcra();

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
    printf("Parabéns conseguis-te encontrar o tesouro!!");
    printf("\n\n\n");
   
	carregarTeclaParaContinuar();
}

void graficoMenuCreditosFinais(){
	//MENU que aparece no final do jogo
	limparEcra();

    printf("\t\n\n\n/\\ /\\ /\\");
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
    printf("\t\n### ##############     ESTiG, Dezembro 2013             ###########");
    printf("\t\n##   #############                                      ###########");
    printf("\t\n##   ##############################################################");
    printf("\n\n\n");
}

void graficoVerMapaduranteJogo(struct Jogador *jogador){
	//menu que mostra o desenho do mapa durante o jogo
	
	limparEcra();
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

	printf("\t\t\t\tM A P A\n\n");

	/*				MAPA	                       */
	printf(" _____________________________________________\n");
	printf("|        |                  |           |     |\n");
	printf("|   0             1                2    |     |\n");
	printf("|___  ___|__________________|_____  ____|     |\n");
	printf("|        |                              |  3  |\n");
	printf("|   4                   5                     |\n");
	printf("|___  ___|_____________  _______________|     |\n");
	printf("|        |          |          |        |__  _|\n");
	printf("|   6    |     7    |   8      |   9    |     |\n");
	printf("|                                       |  10 |\n");
	printf("|________|__________|__________|________|_____|\n\n\n");

	printf("%s estás na sala %d\n\n\n\n", jogador->jogadorNome, jogador->jogadorPosicao);
}

void graficoMenuHistoriaIntro(struct Jogador *jogador){
	limparEcra();
	
	printf("\n###############################################################################");
	printf("\n##                              LOST IN PAST                                 ##");
	printf("\n##                                                                           ##");
	printf("\n##  %s encontrou uma velha máquina do tempo que julgava não funcionar,", jogador->jogadorNome);
	printf("\n## pois a mesma se encontrava com muita ferrugem e algo danificada. Daí,     ##");
	printf("\n## %s pegou em várias ferramentas e passado alguns dias conseguiu", jogador->jogadorNome);
	printf("\n## colocar a máquina a funcionar.                                            ##");
	printf("\n##                                                                           ##");
	printf("\n##  Após a recuperação %s decidiu fazer uma viagem no tempo, para o tempo", jogador->jogadorNome);
	printf("\n## que o fascinava, tempo esse em que reinava o Lord Greg, temível Rei e ao  ##");
	printf("\n## mesmo tempo aventureiro. Lord Greg era o responsável por várias           ##");
	printf("\n## conquistas, várias descobertas importantes e responsável pelo maior       ##");
	printf("\n## império do mundo. %s era um dos seus nobres cavaleiros ao qual foi", jogador->jogadorNome);
	printf("\n## dada uma importante missão: Capturar um tesouro escondido num castelo     ##"); 
	printf("\n## que estava guardado por um terrível monstro.                              ##");
	printf("\n##                                                                           ##");
	printf("\n###############################################################################");
	printf("\n\nPág. 1 / 2 \n\n");
	
	carregarTeclaParaContinuar();
}

void graficoMenuHistoriaIntro2(struct Jogador *jogador){
	limparEcra();
	
	printf("\n###############################################################################");
	printf("\n##                              LOST IN PAST                                 ##");
	printf("\n##                                                                           ##");
	printf("\n##  Reza a história que esse castelo era defindido por um terrível monstro   ##");
	printf("\n## que fazia frente a qualquer pessoa que quisesse apoderar-se do seu        ##");
	printf("\n## tesouro.                                                                  ##");
	printf("\n##                                                                           ##");
	printf("\n##  %s tem a missão de resgastar o tesouro a todo o custo, tendo para isso", jogador->jogadorNome);
	printf("\n## percorrer as várias salas do castelo à procura do tesouro. Por sua vez    ##");
	printf("\n## o monstro irá passeando no castelo, na sua ronda diária de defesa do seu  ##");
	printf("\n## bem precioso.                                                             ##");
	printf("\n##                                                                           ##");
	printf("\n## %s estás preparado?? Vamos começar!                               ", jogador->jogadorNome); 
	printf("\n##                                                                           ##");
	printf("\n###############################################################################");
	printf("\n\nPág. 2 / 2 \n\n");
	
	carregarTeclaParaContinuar();
}


int main(int argc, char* argv[])
{
	struct Jogador jogador;
	struct Adversario adversario;
	struct Celula mapa[SISTEMA_MAPA_MAX_CELULAS];
	char movimento[5];
	int movimentarTesouro = 10;
	int steps = 0; //conta o numero de passos do jogador para esconder o tesouro
	setlocale(LC_ALL, "Portuguese");

	graficoMenuIntro();

	//menu inicial
    graficoMenuMenuPrincipal();
    printf("Insira a opção: ");
	scanf("%s", movimento);

	if ( strcmp(movimento, "1") == 0 ){ //novo jogo
		iniciarJogador(&jogador);
		iniciarAdversario(&adversario);
		
		//verifica se o jogo foi executado em modo "super User"
		if( (argc == 2) && (strcmp(argv[1],"su") == 0) ){
			jogador.jogadorEnergia = JOGADOR_ENERGIA_SU_MODE;
		}
		graficoMenuHistoriaIntro(&jogador);
		graficoMenuHistoriaIntro2(&jogador);
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
		printf( "\n\nPara onde queres ir?\n1. Norte\n2. Sul\n3. Este\n4. Oeste\n5. Ver Mapa\n\n8. Guardar Jogo\n9. Sair do jogo\n\nQual é a opção: ");
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
		if ( strcmp( movimento, "5" ) == 0  ){
			graficoVerMapaduranteJogo(&jogador);
			//system("pause");
			carregarTeclaParaContinuar();
		}
		if ( strcmp( movimento, "8" ) == 0  ){
			//system("cls");
			limparEcra();
			printf("Jogo Guardado...\n\n");
			salvarJogoTXT(&jogador, &adversario);
			salvarJogoBIN(&jogador, &adversario);
			//system("pause");
			carregarTeclaParaContinuar();
		}
		if ( strcmp( movimento, "9" ) == 0  ){
			break; //termina o jogo e mostra a mensagem com info sobre o autor, disciplina, etc
		}

		//esconde o tesouro caso o jogador tenha dado 3 passos
		if (steps == 4){
			mapa->tesouro = 11; //coloca o tesouro oculto (fora do mapa)
			steps = 0;
		}else{
			mapa->tesouro = 10; //coloca novamente o tesouro no mapa
		}
		steps++;

		//verifica se o jogador encontrou o tesouro
		if( jogador.jogadorPosicao == movimentarTesouro ){
			graficoJogoTesouroEncontrado();
			break;
		}

		//movimenta o adversario
		if( strcmp(movimento,"5") != 0 )
			movimentarAdversario(&adversario);

		combatePersonagens(&jogador, &adversario);
		verificaFimJogo(&jogador, &adversario);
		//system( "cls" );
		limparEcra();
	}

	graficoMenuCreditosFinais();
	//system("pause");
	carregarTeclaParaContinuar();
	return 0;
}