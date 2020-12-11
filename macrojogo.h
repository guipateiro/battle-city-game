//GRR20197152 Guilherme Costa Pateiro
//Universidade Federal do Parana , programacao2 - ERE2 A
//ultima edicao: 9/12/2020 19:36
#ifndef MACROJOGO
#define MACROJOGO


#include <allegro5/allegro_ttf.h>
#include "liblista.h"
#include "jogo.h"

#define SPRITEJOGADOR1 "resources/tankaliado1.png"
#define SPRITEJOGADOR2 "resources/tankaliado2.png"
#define SPRITEINIMIGO1 "resources/tankinimigo1.png"
#define SPRITEINIMIGO2 "resources/tenkinimigo2.png"
#define SPRITEPAREDE "resources/Wall.png"
#define SPRITEBARREIRA "resources/barreira.png"
#define PREENCHIMENTO ""
#define SPRITEAGUA "resources/agua.png"
#define SPRITEMATO1 "resources/mato.png"
#define SPRITEMATO2 "resources/mato2.png"
#define SPRITEBLOCO "resources/bloco.png"
#define SPRITEINSGINIA "resources/insignia.png"
#define SPRITENUKE1 "resources/nuke1.png"
#define SPRITENUKE2 "resources/nuke2.png"
#define SPRITEEXPLOSAO "resources/explosao.png"
#define	IMAGEMEU "resources/autorfodaprakrl.png"
#define IMAGEMSCOOBY "resources/pfvmedanota.jpg"
#define FONTECAPTUREIT1 "resources/captureit1.ttf"
#define FONTECAPTUREIT2 "resources/captureit2.ttf"
#define FONTEOPENSANS "resources/OpenSans.ttf"
#define FONTEPIXELAR "resources/BlockStock.ttf"
#define SOMTIRO "resources/somtiro.ogg"
#define SOMINIMIGOMORRE "resources/sommorteinimigo.ogg"
#define SOMNUKE "resources/somnuke.ogg"
#define SOMFUNDO "resources/stickup.ogg"
#define ARQUIVODEPONTOS "resources/highscores.txt"
#define PONTOSCANHAO 200
#define PONTOSNUKE  500
#define LIMITETIRO 1

typedef struct {
  int  score;
  char nome[20];
} tscore;

//inicializa o allegro e imprime o menu principal 
int menuprincipal(ALLEGRO_DISPLAY* disp);

//o jogo em si
int jogando(ALLEGRO_DISPLAY* disp,int cheatcode, int continuar);

//tela de fim de jogo emtrada de pontuacoes 
void fimdejogo(ALLEGRO_DISPLAY* disp,int pontos,int *continuar);

#endif