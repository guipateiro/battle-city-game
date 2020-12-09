//GRR20197152 Guilherme Costa Pateiro
//Universidade Federal do Parana , programacao2 - ERE2 A
//ultima edicao: 8/12/2020 16:01

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"liblista.h"

//inicializacao do TAD lista 
//devolve 1 se foi bem sucedido , 0 caso contrario 
int inicializa_lista(t_lista *l){
    t_nodo *inicio,*fim;
    inicio = (t_nodo *) malloc(sizeof(t_nodo));   //aloca memoria para o nodo inicio  e verifica se foi alocado
    if (inicio == NULL)
      return 0;  
    fim = (t_nodo *) malloc(sizeof(t_nodo));  //aloca memoria para o nodo fim e verifica se foi alocado 
    if (fim == NULL)
      return 0;  
    l->ini = inicio;                 //inicia todos os ponteiros da lista 
    l->fim = fim;
    inicio->prox = fim;
    fim->prev = inicio;
    inicio->prev = NULL;
    fim->prox = NULL;
    l->tam = 0;                   //inicia a lista com tamanho 0
    l->atual = l->ini;            //coloca atual no inicio 
    return 1;
}

//devolve 1 se a lista estiver vazia, 0 caso ela tenho mais de um elemento
int lista_vazia(t_lista *l){
    if (l->tam == 0) 
      return 1;
    return 0; 
}

//insere um novo nodo a partir do nodo inicio
//devolve 1 se for bem sucedido , 0 em caso de erro
int insere_inicio_lista(tsprite sprite, int nlin, int ncol,int direcao, t_lista *l){
    t_nodo *novo;
    t_nodo *aux;
    novo = (t_nodo *) malloc(sizeof(t_nodo)); // aloca memoria para o novo nodo e verifica se foi alocado   
    if (novo == NULL)
      return 0;  

  novo->sprite = sprite;            //modifica os ponteiros para ter um novo elemento
  novo->nlin = nlin;
  novo->ncol = ncol; 
  novo->direcao = direcao;

  aux = l->ini->prox;
    l->ini->prox = novo;
    aux->prev = novo;
    novo->prox = aux;
    novo->prev = l->ini;
    l->tam ++;                     //incrementa o tamanho da lista 
    return 1; 
}   

//responde em tam o numero de elementos da lista
//caso a lista tenha sido destruida ele retorna 0
int tamanho_lista(int *tam, t_lista *l){
    *tam = l->tam;
    if (l->tam < 0)
      return 0;
    return 1;
 } 

//insere um novo nodo antes do nodo fim 
//devolve 1 se for bem sucedido , 0 em caso de erro
int insere_fim_lista(tsprite sprite, int nlin, int ncol,int direcao, t_lista *l){
    if (lista_vazia(l)){
      insere_inicio_lista(sprite,nlin,ncol,direcao,l);
      return 1;
    }  
    else{
        t_nodo *novo;
        t_nodo *aux;
        novo = (t_nodo *) malloc(sizeof(t_nodo));   // aloca memoria para o novo nodo e verifica se foi alocado   
        if (novo == NULL)
            return 0;

        novo->sprite = sprite;              //modifica os ponteiros para ter um novo elemento
        novo->nlin = nlin;
        novo->ncol = ncol;  
        novo->direcao = direcao;

        aux = l->fim->prev;
        aux->prox = novo;
        novo->prev = aux;
        novo->prox = l->fim; 
        l->fim->prev = novo;
        l->tam++;                           //incrementa o tamanho da lista            
        return 1; 
    } 
}

//remove um nodo a partir do nodo inicio 
//retorna 1 caso bem sucedido , 0 caso tenha occorido algum erro 
int remove_inicio_lista(tsprite *sprite, int *nlin, int *ncol,int *direcao, t_lista *l){
  t_nodo *aux;
  t_nodo *aux2;
  if (l->ini->prox == l->fim )
    return 0;

   aux = l->ini->prox;            //modifica os ponteiros para nao ter mais essse nodo  
   aux2 = aux->prox;
   l->ini->prox = aux2;
   aux2->prev = l->ini;
   aux->prox = NULL;
   aux->prev = NULL;

   *sprite = aux->sprite;         //devolve os elementos do nodo 
   *nlin = aux->nlin;
   *ncol = aux->ncol;    
   *direcao = aux->direcao; 

   l->tam--;                      //decrementa o tamanho 
   free(aux);                     //libera a memoria alocada no nodo 
   return 1; 

}

// remove um nodo antes do nodo fim 
//retorna 1 caso bem sucedido , 0 caso tenha occorido algum erro 
int remove_fim_lista(tsprite *sprite, int *nlin, int *ncol,int *direcao, t_lista *l){
    t_nodo *aux;
    t_nodo *aux2;
    if (l->fim->prev == l->ini )
      return 0; 
  
    aux = l->fim->prev;         //modifica os ponteiros para nao ter mais essse nodo
    aux2 = aux->prev;
    l->fim->prev = aux2;
    aux2->prox = l->fim;
    aux->prox = NULL;
    aux->prev = NULL;

    *sprite = aux->sprite;      //devolve os elementos do nodo 
    *nlin = aux->nlin;
    *ncol = aux->ncol;
    *direcao = aux->direcao; 

    l->tam--;                   //decrementa o tamanho 
  free(aux);                    //libera a memoria alocada no nodo
  return 1;
}   


//coloca o nodo atual no primeiro nodo apos inicio 
int inicializa_atual_inicio(t_lista *l){
   l->atual = l->ini->prox;
   return 1; 
}

//coloca o nodo atual no ultimo nodo ates de fim  
int inicializa_atual_fim(t_lista *l){
    l->atual = l->fim->prev; 
    return 1;
} 

//faz o nodo atual ir para o proximo elemento da lista
void incrementa_atual(t_lista *l){
    if (l->atual->prox != NULL)
      l->atual = l->atual->prox;
    else 
      l->atual = NULL;  
} 

//o nodo atual ir para o elemento anterior da lista
void decrementa_atual(t_lista *l){
  if (l->atual->prev != NULL)
    l->atual = l->atual->prev;
  else 
    l->atual = NULL;
}  

//devolve os elementos que compoem aquele nodo da lista
//retorna 1 caso bem sucedido , 0 caso tenha occorido algum erro 
int consulta_item_atual(tsprite *sprite, int *nlin, int *ncol,int *direcao, t_lista *l){
  if (l->atual->prox == NULL || l->atual->prev == NULL)
      return 0;

    *sprite = l->atual->sprite;       //devolve os elementos do nodo 
    *nlin = l->atual->nlin;
    *ncol = l->atual->ncol;
    *direcao = l->atual->direcao; 

  return 1; 
}

//modifica o nodo atual com o parametros da funcao
//retorna 1 caso bem sucedido , 0 caso tenha occorido algum erro 
int modifica_item_atual(tsprite sprite,int nlin, int ncol ,int direcao,t_lista *l){
  if (l->atual->prox == NULL || l->atual->prev == NULL)
      return 0;

  l->atual->sprite = sprite;      //recebe os elementos passdao pela funcao
  l->atual->nlin = nlin;
  l->atual->ncol = ncol; 
  l->atual->direcao = direcao; 

  return 1;
}

//remove da lista o elemento apontado por atual 
//retorna 1 caso bem sucedido , 0 caso tenha occorido algum erro 
int remove_item_atual(tsprite *sprite, int *nlin, int *ncol,int *direcao, t_lista *l){
    t_nodo *auxprox;
    t_nodo *auxprev;
    t_nodo *aux;
    if (l->atual->prox == NULL || l->atual->prev == NULL)
      return 0;
  
    auxprev = l->atual->prev;          //modifica os ponteiros para nao ter mais essse nodo
    auxprox = l->atual->prox;
    aux = l->atual;
    l->atual = l->atual->prox;
    if (l->atual->prox == NULL)
      l->atual->prox = l->fim;
    auxprev->prox = auxprox;
    auxprox->prev = auxprev;
    aux->prev = NULL;
    aux->prox = NULL;

    *sprite = aux->sprite;            //devolve os elementos do nodo 
    *nlin = aux->nlin;
    *ncol = aux->ncol;
    *direcao = aux->direcao;

  l->tam--;                           //decrementa o tamanho 
    free(aux);                        //libera a memoria alocada no nodo  
    return 1; 
}

//remove todos os nodos e destroi todos os ponteiros,inutilizando a lista 
void destroi_lista(t_lista *l){
  int i ,tam ,o,p,dir;
  tsprite sprite;   
  l->atual = NULL;
  tamanho_lista(&tam , l );         //pega o tamanho da lista para o loop
  for (i = 1 ; i <= tam ; i++)      //loop de remocao de elementos da lista 
    remove_fim_lista (&sprite ,&o ,&p,&dir,l);
  free(l->ini);
  free(l->fim);
  l->ini = NULL;
  l->fim = NULL;
  l->tam = -1; 

}

//remove todos so elementosda lista, mas ela ainda pode ser utilizada
void esvazia_lista(t_lista *l){
   int i, dir, lin, col;
  tsprite sprite;
  int tam;
  tamanho_lista(&tam,l);        //pega o tamanho da lista para o loop
  for(i = 0 ; i < tam ; i++)    //loop de remocao de elementos da lista 
    remove_inicio_lista(&sprite,&lin,&col,&dir,l);
}

//imprime em stdout todos os elementos da lista e seus conteudos
void imprime_lista(t_lista *l){
  int i, dir, lin, col;
  tsprite sprite;
  int tam;
  tamanho_lista(&tam,l);                //pega o tamanho da lista para o loop
  inicializa_atual_inicio(l);
  for(i = 0 ; i < tam ; i++){           //loop de impressao da lista 
    consulta_item_atual(&sprite,&lin,&col,&dir,l);  //recebe as variaveis do nodo atual
    printf("Elemento: %i lin: %i col: %i dir: %i \n", i+1, lin, col, dir);   //imprime essas variaveis
    incrementa_atual(l); 
  } 
}