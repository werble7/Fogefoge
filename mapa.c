#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapa.h"

int pode_andar(MAPA* m, char personagem, int x, int y) {
	return 
		eh_valida(m, x, y) && 
		!eh_parede(m, x, y) &&
		!eh_personagem(m, personagem, x, y);
}


int eh_valida(MAPA* m, int x, int y) {
	if(x >= m->linhas) 
		return 0;
	if(y >= m->colunas) 
		return 0;

	return 1;	
}

int eh_personagem(MAPA* m, char personagem, int x, int y) {
	return
		m->matriz[x][y] == personagem;
}

int eh_parede(MAPA* m, int x, int y) {
	return 
		m->matriz[x][y] == PAREDE_VERTICAL ||
		m->matriz[x][y] == PAREDE_HORIZONTAL;
}

void copiar_mapa(MAPA* destino, MAPA* origem){
	destino->linhas = origem->linhas;
	destino->colunas = origem->colunas;

	alocar_mapa(destino);
	for(int i = 0; i < origem->linhas; i++){
		strcpy(destino->matriz[i], origem->matriz[i]);
	}
}

int verificar_vazio(MAPA* m, int x, int y){
	return m->matriz[x][y] == VAZIO;
}

void andar_no_mapa(MAPA* m, int origemx, int origemy, int destinox, int destinoy){
	char personagem = m->matriz[origemx][origemy];
	m->matriz[destinox][destinoy] = personagem;
	m->matriz[origemx][origemy] = VAZIO;
}

int encontrar_mapa(MAPA* m, POSICAO* p, char c){
	for(int i = 0; i < m->linhas; i++){
		for(int j = 0; j < m->colunas; j++){
			if(m->matriz[i][j] == c){
				p->x = i;
				p->y = j;
				return 1;
			}
		}
	}
	return 0;
}

void ler_mapa(MAPA* m){
	FILE* f;
	f = fopen("mapa.txt", "r");

	if(f == 0){
		printf("Erro na leitura do mapa\n");
		exit(1);
	}

	fscanf(f, "%d %d", &(m->linhas), &(m->colunas));
	alocar_mapa(m);

	for(int i = 0; i < 5; i++){
		fscanf(f, "%s", m->matriz[i]);
	}

	fclose(f);
}

void alocar_mapa(MAPA* m){
	m->matriz = malloc(sizeof(char*) * m->linhas);

	for(int i = 0; i < m->linhas; i++){
		m->matriz[i] = malloc(sizeof(char) * (m->colunas+1));
	}
}

void liberar_mapa(MAPA* m){
	for(int i = 0; i < m->linhas; i++){
		free(m->matriz[i]);
	}

	free(m->matriz);
}