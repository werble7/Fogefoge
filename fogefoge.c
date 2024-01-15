#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fogefoge.h"
#include "mapa.h"
#include "ui.h"

MAPA m;
POSICAO heroi;
int tem_pilula;

int direcao_fantasma(int origemx, int origemy, int* destinox, int* destinoy){
	int opcoes[4][2] = {
		{origemx, origemy + 1},
		{origemx, origemy - 1},
		{origemx + 1, origemy},
		{origemx - 1, origemy}
	};

	srand(time(0));
	for(int i = 0; i < 10; i++){
		int posicao = rand() % 4;
		if(pode_andar(&m, FANTASMA, opcoes[posicao][0], opcoes[posicao][1])){
			*destinox = opcoes[posicao][0];
			*destinoy = opcoes[posicao][1];

			return 1;
		}
	}
	return 0;
}

void fantasmas(){
	MAPA copia;

	copiar_mapa(&copia, &m);

	for(int i = 0; i < m.linhas; i++){
		for(int j = 0; j < m.colunas; j++){

			if(copia.matriz[i][j] == FANTASMA){

				int destinox;
				int destinoy;
				int encontrou = direcao_fantasma(i, j, &destinox, &destinoy);

				if(encontrou){
					andar_no_mapa(&m, i, j, destinox, destinoy);
				}
			}
		}
	}

	liberar_mapa(&copia);
}

int verificar_direcao(char direcao){
	return direcao == ESQUERDA ||
		direcao == CIMA ||
		direcao == DIREITA || 
		direcao == BAIXO;
}

void move(char direcao){
	if(!verificar_direcao(direcao))
		return;

	int proximox = heroi.x;
	int proximoy = heroi.y;

	switch(direcao) {
		case ESQUERDA:
			proximoy--;
			break;
		case CIMA:
			proximox--;
			break;
		case BAIXO:
			proximox++;
			break;
		case DIREITA:
			proximoy++;
			break;
	}

	if(!pode_andar(&m, HEROI, proximox, proximoy))
		return;

	if(eh_personagem(&m, PILULA, proximox, proximoy)){
		tem_pilula = 1;
	}

	andar_no_mapa(&m, heroi.x, heroi.y, proximox, proximoy);
	heroi.x = proximox;
	heroi.y = proximoy;

}

int acabou(){
	POSICAO pos;
	int encontrou_fogefoge = encontrar_mapa(&m, &pos, HEROI);
	int encontrou_fantasma = encontrar_mapa(&m, &pos, FANTASMA);
	return !encontrou_fogefoge || !encontrou_fantasma;
}

void explode_pilula(){
	if(!tem_pilula) return;
	explode_pilula_direcao(heroi.x, heroi.y, 0, 1, 3); // explode direita
	explode_pilula_direcao(heroi.x, heroi.y, 0, -1, 3); // explode esquerda
	explode_pilula_direcao(heroi.x, heroi.y, 1, 0, 3); // explode cima
	explode_pilula_direcao(heroi.x, heroi.y, -1, 0, 3); // explode baixo

	tem_pilula = 0;
}


void explode_pilula_direcao(int x, int y, int somax, int somay, int qtd){

	if(qtd == 0) return;

	int novox = x + somax;
	int novoy = y + somay;

	if(!eh_valida(&m, novox, novoy)) return;
	if(eh_parede(&m, novox, novoy)) return;

	m.matriz[novox][novoy] = VAZIO;
	explode_pilula_direcao(novox, novoy, somax, somay, qtd-1);
}


int main(){
	ler_mapa(&m);
	encontrar_mapa(&m, &heroi, HEROI);
	
	do {
		system("cls");
		printf("Tem pilula: %s\n", (tem_pilula ? "SIM" : "NAO"));
		imprimir_mapa(&m);

		char comando;
		scanf(" %c", &comando);
		move(comando);
		if(comando == BOMBA) explode_pilula();
		fantasmas();

	} while(!acabou());

	system("cls");
	POSICAO pos;
	if (!encontrar_mapa(&m, &pos, FANTASMA)){
		printf("\nParabens, voce ganhou!\n\n");
		printf("       ___________      \n");
    	printf("      '._==_==_=_.'     \n");
   		printf("      .-\\:      /-.    \n");
   		printf("     | (|:.     |) |    \n");
   		printf("      '-|:.     |-'     \n");
   		printf("        \\::.    /      \n");
   		printf("         '::. .'        \n");
   		printf("           ) (          \n");
    	printf("         _.' '._        \n");
    	printf("        '-------'       \n\n");

	} else {
		printf("\nPuxa, voce pego pelo fantasma!\n");
    	printf("    _______________         \n");
    	printf("   /               \\       \n"); 
    	printf("  /                 \\      \n");
    	printf("//                   \\/\\  \n");
    	printf("\\|   XXXX     XXXX   | /   \n");
    	printf(" |   XXXX     XXXX   |/     \n");
    	printf(" |   XXX       XXX   |      \n");
    	printf(" |                   |      \n");
    	printf(" \\__      XXX      __/     \n");
    	printf("   |\\     XXX     /|       \n");
    	printf("   | |           | |        \n");
    	printf("   | I I I I I I I |        \n");
    	printf("   |  I I I I I I  |        \n");
    	printf("   \\_             _/       \n");
    	printf("     \\_         _/         \n");
    	printf("       \\_______/           \n");
	}
	
	liberar_mapa(&m);
}
