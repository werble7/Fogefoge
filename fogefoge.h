#ifndef _FOGEFOGE_H_
#define _FOGEFOGE_H_

#define CIMA 'w'
#define BAIXO 's'
#define ESQUERDA 'a'
#define DIREITA 'd'
#define BOMBA 'b'

void move(char direcao);
int acabou();
int verificar_direcao(char direcao);
void fantasmas();
int direcao_fantasma(int origemx, int origemy, int* destinox, int* destinoy);
void explode_pilula();
void explode_pilula_direcao(int x, int y, int somax, int somay, int qtd);

#endif