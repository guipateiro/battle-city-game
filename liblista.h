//GRR20197152 Guilherme Costa Pateiro
//Universidade Federal do Parana , programacao2 - ERE2 A
//ultima edicao: 8/12/2020 16:02
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

//inicializacao do TAD lista 
int inicializa_lista(t_lista *l);

//responde se a lista esta vazia 
int lista_vazia(t_lista *l);

//insere um novo nodo a partir do nodo inicio
int insere_inicio_lista(tsprite sprite, int nlin, int ncol,int direcao, t_lista *l);

//responde em tam o numero de elementos da lista
int tamanho_lista(int *tam, t_lista *l);

//insere um novo nodo antes do nodo fim 
int insere_fim_lista(tsprite sprite, int nlin, int ncol,int direcao, t_lista *l);

//remove um nodo a partir do nodo inicio 
int remove_inicio_lista(tsprite *sprite, int *nlin, int *ncol,int *direcao, t_lista *l);

// remove um nodo antes do nodo fim 
int remove_fim_lista(tsprite *sprite, int *nlin, int *ncol,int *direcao, t_lista *l);

//coloca o nodo atual no primeiro nodo apos inicio 
int inicializa_atual_inicio(t_lista *l);
  
//coloca o nodo atual no ultimo nodo ates de fim   
int inicializa_atual_fim(t_lista *l);

//faz o nodo atual ir para o proximo elemento da lista
void incrementa_atual(t_lista *l);

//o nodo atual ir para o elemento anterior da lista
void decrementa_atual(t_lista *l);

//devolve os elementos que compoem aquele nodo da lista
int consulta_item_atual(tsprite *sprite, int *nlin, int *ncol,int *direcao, t_lista *l);

//modifica o nodo atual com o parametros da funcao
int modifica_item_atual(tsprite sprite,int nlin, int ncol ,int direcao,t_lista *l);

//remove da lista o elemento apontado por atual 
int remove_item_atual(tsprite *sprite, int *nlin, int *ncol,int *direcao, t_lista *l);

//remove todos os nodos e destroi todos os ponteiros,inutilizando a lista 
void destroi_lista(t_lista *l);

//remove todos so elementosda lista, mas ela ainda pode ser utilizada
void esvazia_lista(t_lista *l);

//imprime em stdout todos os elementos da lista e seus conteudos
void imprime_lista(t_lista *l);

#endif