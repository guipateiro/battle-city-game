//GRR20197152 Guilherme Costa Pateiro
//Universidade Federal do Parana , programacao2 - ERE2 A
//ultima edicao: 9/12/2020 19:41
#ifndef jogo
#define jogo

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "liblista.h"

#define FREQINIMIGOS 20
#define FREQNUKE 5
#define MOVIMENTACAOINIMIGOS 300
#define CHANCEINIMIGOTIRO 60 

//verifica se uma variavel foi iniciada, parando o programa q escrevendo o erro em stdout
void must_init(bool test, const char *description);

//cria todas as barreiras, em caso de erro, para o programa 
void cria_barreiras(t_lista *l,tsprite sprite);

//cria todas as aguas, em caso de erro, para o programa 
void cria_agua(t_lista *l,tsprite sprite);

//cria todos os blocos, em caso de erro, para o programa 
void cria_blocos(t_lista *l,tsprite sprite);

//cria todos os matos, em caso de erro, para o programa 
void cria_matos(t_lista *l,tsprite sprite);

//cria todas as paredes, em caso de erro, para o programa 
void cria_paredes(t_lista *l,tsprite sprite);

//cria todas as aguas, em caso de erro, para o programa 
void cria_jogador(t_lista *l, int x, int y,tsprite sprite);

//cria todas as aguas, em caso de erro, para o programa 
void cria_tiro(t_lista *l,int lin, int col, int dir,tsprite sprite);

//cria todas as aguas, em caso de erro, para o programa 
void cria_insignia(t_lista *l,tsprite sprite);

//cria todas as aguas, em caso de erro, para o programa 
void atualiza_jogador(t_lista *l ,int x, int y, int dir,tsprite sprite);

//cria nukes, em caso de erro, para o programa 
void inicia_nuke(t_lista *l,tsprite sprite);

//se um tank for criado onde ja tem um tank, retorna 1, caso contrario, retorna 0
int colisao_criando_inimigo(int lin1,int col1,int tamlista,t_lista *l);

//cria inimigos, em caso de erro, para o programa 
//caso um inimigo seja criado onde ja tem um inimigo, cancela a criacao 
void inicia_inimigos(t_lista *l,tsprite sprite);

//cria bombas a partir dos elementos de outra lista, em caso de erro, para o programa
void inicia_bombas(t_lista *l,t_lista *lista1,tsprite sprite);

//verifica e houve uma colisao entre 2 listas 
//caso tenha uma colisao retorna 1, caso contrario retorna 0 
//a comparacao deve ocorer entre 1 sprite de 14 pixel centrelizado se outro de 16 pixels de tamanho total 
int colisao_tank_parede(t_lista *lista1,t_lista *lista2);

//verifica e houve uma colisao entre 2 listas 
//caso tenha uma colisao retorna 1, caso contrario retorna 0 
//a comparacao deve ocorer entre 1 sprite de 14 pixel centrelizado se outro de 32 pixels de tamanho total 
//caso o sprite da lista 1 seja invencivel sempre ratornara 0
int colisao_tank_bloco(t_lista *lista1,t_lista *lista2);

//verifica e houve uma colisao entre 2 listas 
//caso tenha uma colisao retorna 1, caso contrario retorna 0 
//a comparacao deve ocorer entre 1 sprite de 14 pixel centrelizado se outro de 32 pixels de tamanho total 
int colisao_tank_bloco2(t_lista *lista1,t_lista *lista2);

//verifica e houve uma colisao entre 2 listas 
//caso haja uma colisao, ambos os elementos da lista sao removidos
int colisao_tiro_parede(t_lista *lista1,t_lista *lista2);

//verifica e houve uma colisao entre 2 listas 
//caso haja uma colisao, ambos os elementos da lista sao removidos
//retorna 1 caso tenha havido uma colisao 0 caso contrario 
int colisao_tiro_bloco(t_lista *lista1,t_lista *lista2);

//verifica e houve uma colisao entre 2 listas 
//caso haja uma colisao, ambos os elementos da lista sao removidos
//caso haja uma colisao, insere um elemento na lista 3 com o sprite 3
//retorna o numero de colisoes que ocorreram
int colisao_tank_tiro(t_lista *lista1, t_lista *lista2,t_lista *lista3,tsprite sprite3);

//verifica e houve uma colisao entre 2 listas 
//caso haja uma colisao, todos os elementos da lista 2 e lista 3 sao removidos 
//retorna o numero de elementos removidos da lista 3
int colisao_tank_nuke(t_lista *lista1,t_lista *lista2,t_lista *lista3);

//atualiza a movimentacao dos inimigos
//se baseia na direcao atual do inimigo
//puequena chance de mudar a direcao do inimigo quando ele for atualizado
//verifica a calisao entre os inimigo e todos os blocos que impedem a movimentacao
//impede que os inimigo morram para agua 
void atualiza_inimigos(t_lista *l,t_lista *paredes,t_lista *blocos,t_lista *aguas);

//movimenta os tiros
//se baseia na direcao que ele esta 
//somente movimenta elementos em linha reta 
void atualiza_tiros(t_lista *l);

//imprime vidas no canto da tela, se baseia no munero V (numero de vidas)
void imprime_vidas(int v,tsprite sprite,int ver);

//imprime ,em lin/col,uma lista
//percorre uma lista imprimindo 
//a cada frame, incremeta  um contador em cada elemento da lista, quando o contador chegar em 5, o elemento sai da lista 
void imprime_explosoes(t_lista *lista1);

//imprime na tela, em lin/col um sprite
//o sprite que vai ser imprido se baseia em ver 
void inicia_sprite_ambiente(tsprite *sprite,int lin ,int col,int dir,int ver);

//percorre uma lista, imprimindo todos os elementos dela
void imprime_ambiente(t_lista *l,int ver);

//imprime na tela, em lin/col um sprite
//o sprite que vai ser imprido se baseia em versao
//a direcao depende de ver
void inicia_sprite(tsprite *sprite,int lin ,int col,int ver, int versao);

//percorre uma lista de tanks, imprimindo todos elementos 
//a direcao de um sprite se baseiem dir 
void imprime_tanks(t_lista *l, int versao);

//percorre uma lista, porem a unica parte utilizada sao lin/col 
//imprime uma circulo lo local de lin/col 
//a cor do circulo se baseia em R G B 
void imprime_tiros(t_lista *l,int R, int G, int B);



#endif
