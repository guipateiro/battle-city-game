#ifndef liblista
#define liblista 

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

typedef struct {
  int  tamlin;
  int  tamcol;
  ALLEGRO_BITMAP* corpo1;
  ALLEGRO_BITMAP* corpo2;
  ALLEGRO_BITMAP* corpo3;
  int invencivel;
} tsprite; 

struct t_nodo {
   	tsprite sprite;
   	int nlin;
   	int ncol; 
    int direcao;
    struct t_nodo *prox;
    struct t_nodo *prev;
};
typedef struct t_nodo t_nodo;

struct t_lista {
    t_nodo *ini;
    t_nodo *atual;
    t_nodo *fim;
    int tam;
};
typedef struct t_lista t_lista;


int inicializa_lista(t_lista *l);

int insere_inicio_lista(tsprite sprite, int nlin, int ncol,int direcao, t_lista *l);

int tamanho_lista(int *tam, t_lista *l);

int insere_fim_lista(tsprite sprite, int nlin, int ncol,int direcao, t_lista *l);

int remove_inicio_lista(tsprite *sprite, int *nlin, int *ncol,int *direcao, t_lista *l);

int remove_fim_lista(tsprite *sprite, int *nlin, int *ncol,int *direcao, t_lista *l);

int inicializa_atual_inicio(t_lista *l);
  
int inicializa_atual_fim(t_lista *l);

void incrementa_atual(t_lista *l);

void decrementa_atual(t_lista *l);

int consulta_item_atual(tsprite *sprite, int *nlin, int *ncol,int *direcao, t_lista *l);

int modifica_item_atual(tsprite sprite,int nlin, int ncol ,int direcao,t_lista *l);

int remove_item_atual(tsprite *sprite, int *nlin, int *ncol,int *direcao, t_lista *l);

void destroi_lista(t_lista *l);

void imprime_lista(t_lista *l);

#endif