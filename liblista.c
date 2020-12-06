#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"liblista.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

int inicializa_lista(t_lista *l){
    t_nodo *inicio,*fim;
    inicio = (t_nodo *) malloc(sizeof(t_nodo));
    if (inicio == NULL)
      return 0;  
    fim = (t_nodo *) malloc(sizeof(t_nodo));
    if (fim == NULL)
      return 0;  
    l->ini = inicio;
    l->fim = fim;
    inicio->prox = fim;
    fim->prev = inicio;
    inicio->prev = NULL;
    fim->prox = NULL;
    l->tam = 0;
    l->atual = l->ini; 
    return 1;
}

int lista_vazia(t_lista *l){
    if (l->tam == 0) 
      return 1;
    return 0; 
}

int insere_inicio_lista(tsprite sprite, int nlin, int ncol,int direcao, t_lista *l){
    t_nodo *novo;
    t_nodo *aux;
    novo = (t_nodo *) malloc(sizeof(t_nodo));
    if (novo == NULL)
      return 0;  

  novo->sprite = sprite; 
  novo->nlin = nlin;
  novo->ncol = ncol; 
  novo->direcao = direcao;

  aux = l->ini->prox;
    l->ini->prox = novo;
    aux->prev = novo;
    novo->prox = aux;
    novo->prev = l->ini;
    l->tam ++;
    return 1; 
}   

int tamanho_lista(int *tam, t_lista *l){
    *tam = l->tam;
    if (l->tam < 0)
      return 0;
    return 1;
 } 

int insere_fim_lista(tsprite sprite, int nlin, int ncol,int direcao, t_lista *l){
    if (lista_vazia(l)){
      insere_inicio_lista(sprite,nlin,ncol,direcao,l);
      return 1;
    }  
    else{
        t_nodo *novo;
        t_nodo *aux;
        novo = (t_nodo *) malloc(sizeof(t_nodo));
        if (novo == NULL)
            return 0;

        novo->sprite = sprite; 
        novo->nlin = nlin;
        novo->ncol = ncol;  
        novo->direcao = direcao;

        aux = l->fim->prev;
        aux->prox = novo;
        novo->prev = aux;
        novo->prox = l->fim; 
        l->fim->prev = novo;
        l->tam++;
        return 1; 
    } 
}

int remove_inicio_lista(tsprite *sprite, int *nlin, int *ncol,int *direcao, t_lista *l){
  t_nodo *aux;
  t_nodo *aux2;
  if (l->ini->prox == l->fim )
    return 0;

   aux = l->ini->prox; 
   aux2 = aux->prox;
   l->ini->prox = aux2;
   aux2->prev = l->ini;
   aux->prox = NULL;
   aux->prev = NULL;

   *sprite = aux->sprite;
   *nlin = aux->nlin;
   *ncol = aux->ncol;    
   *direcao = aux->direcao; 

   l->tam--;
   free(aux);  
   return 1; 

}

int remove_fim_lista(tsprite *sprite, int *nlin, int *ncol,int *direcao, t_lista *l){
    t_nodo *aux;
    t_nodo *aux2;
    if (l->fim->prev == l->ini )
      return 0; 
  
    aux = l->fim->prev; 
    aux2 = aux->prev;
    l->fim->prev = aux2;
    aux2->prox = l->fim;
    aux->prox = NULL;
    aux->prev = NULL;

    *sprite = aux->sprite;
    *nlin = aux->nlin;
    *ncol = aux->ncol;
    *direcao = aux->direcao; 

    l->tam--;
  free(aux);
  return 1;
}   


int inicializa_atual_inicio(t_lista *l){
   l->atual = l->ini->prox;
   return 1; 
}
  
int inicializa_atual_fim(t_lista *l){
    l->atual = l->fim->prev; 
    return 1;
} 

void incrementa_atual(t_lista *l){
    if (l->atual->prox != NULL)
      l->atual = l->atual->prox;
    else 
      l->atual = NULL;  
} 

void decrementa_atual(t_lista *l){
  if (l->atual->prev != NULL)
    l->atual = l->atual->prev;
  else 
    l->atual = NULL;
}  

int consulta_item_atual(tsprite *sprite, int *nlin, int *ncol,int *direcao, t_lista *l){
  if (l->atual->prox == NULL || l->atual->prev == NULL)
      return 0;

    *sprite = l->atual->sprite;
    *nlin = l->atual->nlin;
    *ncol = l->atual->ncol;
    *direcao = l->atual->direcao; 

  return 1; 
}


int modifica_item_atual(tsprite sprite,int nlin, int ncol ,int direcao,t_lista *l){
  if (l->atual->prox == NULL || l->atual->prev == NULL)
      return 0;

  l->atual->sprite = sprite;
  l->atual->nlin = nlin;
  l->atual->ncol = ncol; 
  l->atual->direcao = direcao; 

  return 1;
}

int remove_item_atual(tsprite *sprite, int *nlin, int *ncol,int *direcao, t_lista *l){
    t_nodo *auxprox;
    t_nodo *auxprev;
    t_nodo *aux;
    if (l->atual->prox == NULL || l->atual->prev == NULL)
      return 0;
  
    auxprev = l->atual->prev;
    auxprox = l->atual->prox;
    aux = l->atual;
    l->atual = l->atual->prox;
    if (l->atual->prox == NULL)
      l->atual->prox = l->fim;
    auxprev->prox = auxprox;
    auxprox->prev = auxprev;
    aux->prev = NULL;
    aux->prox = NULL;

    *sprite = aux->sprite;
    *nlin = aux->nlin;
    *ncol = aux->ncol;
    *direcao = aux->direcao;

  l->tam--; 
    free(aux);
    return 1; 
}

void destroi_lista(t_lista *l){
  int i ,tam ,o,p,dir;
  tsprite sprite;   
  l->atual = NULL;
  tamanho_lista(&tam , l );
  for (i = 1 ; i <= tam ; i++)
    remove_fim_lista (&sprite ,&o ,&p,&dir,l);
  free(l->ini);
  free(l->fim);
  l->ini = NULL;
  l->fim = NULL;
  l->tam = -1; 

}

void imprime_lista(t_lista *l){
  int i, dir, lin, col;
  tsprite sprite;
  int tam;
  tamanho_lista(&tam,l);
  inicializa_atual_inicio(l);
  for(i = 0 ; i < tam ; i++){
    consulta_item_atual(&sprite,&lin,&col,&dir,l);
    printf("Elemento: %i lin: %i col: %i dir: %i \n", i+1, lin, col, dir);
    incrementa_atual(l); 
  } 
}