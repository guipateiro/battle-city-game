#ifndef jogo
#define jogo

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "liblista.h"


void must_init(bool test, const char *description);

void cria_barreiras(t_lista *l,tsprite sprite);

void cria_agua(t_lista *l,tsprite sprite);

void cria_blocos(t_lista *l,tsprite sprite);

void cria_matos(t_lista *l,tsprite sprite);

void cria_paredes(t_lista *l,tsprite sprite);

void cria_jogador(t_lista *l, int x, int y,tsprite sprite);

void atualiza_jogador(t_lista *l ,int x, int y, int dir,tsprite sprite);

void inicia_sprite(tsprite *sprite,int lin ,int col,int ver, int versao);

void imprime_tanks(t_lista *l, int versao);

void imprime_tiros(t_lista *l,int R, int G, int B);

void cria_tiro(t_lista *l,int lin, int col, int dir,tsprite sprite);

void atualiza_tiros(t_lista *l);

void inicia_sprite_ambiente(tsprite *sprite,int lin ,int col,int dir,int ver);

void imprime_ambiente(t_lista *l,int ver);

void cria_insignia(t_lista *l,tsprite sprite);

int colisao_tank_parede(t_lista *lista1,t_lista *lista2);

int colisao_tank_bloco(t_lista *lista1,t_lista *lista2);

int colisao_tank_bloco2(t_lista *lista1,t_lista *lista2);

int colisao_tiro_parede(t_lista *lista1,t_lista *lista2);

int colisao_tiro_bloco(t_lista *lista1,t_lista *lista2);

void inicia_nuke(t_lista *l,tsprite sprite);

int colisao_criando_inimigo(int lin1,int col1,int tamlista,t_lista *l);

void inicia_inimigos(t_lista *l,tsprite sprite);

void atualiza_inimigos(t_lista *l,t_lista *paredes,t_lista *blocos,t_lista *aguas);

void inicia_bombas(t_lista *l,t_lista *lista1,tsprite sprite);

int colisao_tank_tiro(t_lista *lista1, t_lista *lista2,t_lista *lista3,tsprite sprite3);

int colisao_tank_nuke(t_lista *lista1,t_lista *lista2,t_lista *lista3);

void imprime_vidas(int v,tsprite sprite,int ver);

void imprime_explosoes(t_lista *lista1);



#endif