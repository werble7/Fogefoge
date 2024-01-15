#ifndef _MAPA_H_
#define _MAPA_H_

#define HEROI '@'
#define FANTASMA 'F'
#define VAZIO '.'
#define PAREDE_VERTICAL '|'
#define PAREDE_HORIZONTAL '-'
#define PILULA 'P'

struct mapa{
	char** matriz;
	int linhas;
	int colunas;
};

typedef struct mapa MAPA;

struct posicao{
	int x;
	int y;
};

typedef struct posicao POSICAO;

void ler_mapa(MAPA* m);
void alocar_mapa(MAPA* m);
void liberar_mapa(MAPA* m);
int encontrar_mapa(MAPA* m, POSICAO* p, char c);
int eh_valida(MAPA* m, int x, int y);
int verificar_vazio(MAPA* m, int x, int y);
void andar_no_mapa(MAPA* m, int origemx, int origemy, int destinox, int destinoy);
void copiar_mapa(MAPA* destino, MAPA* origem);
int pode_andar(MAPA* m, char personagem, int x, int y);
int eh_personagem(MAPA* m, char personagem, int x, int y);
int eh_parede(MAPA* m, int x, int y);

#endif