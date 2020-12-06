//sim o mazieiro fico maluco e decidiu q eu sei fazer um jogo em 20 dias
//Guilherme Costa Pateiro GRR20197152 
//programacao 2 ERE-2A
//em homenagem ao mazieiro q acha q eu n tenho outras materias no periodo especial
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "liblista.h"


#define SPRITEJOGADOR1 "resources/tankaliado1.png"
#define SPRITEJOGADOR2 "resources/tankaliado2.png"
#define SPRITEINIMIGO1 "resources/tankinimigo1.png"
#define SPRITEINIMIGO2 "resources/tenkinimigo2.png"
#define SPRITEPAREDE "resources/Wall.png"
#define SPRITEBARREIRA "resources/barreira.png"
#define PREENCHIMENTO ""
#define SPRITEAGUA "resources/agua.png"
#define SPRITEMATO "resources/mato.png"
#define SPRITEBLOCO "resources/bloco.png"
#define SPRITEINSGINIA "resources/insignia.png"
#define SPRITENUKE "resources/nuke1.png"
#define PONTOSCANHAO 200
#define PONTOSNUKE  500
#define LIMITETIRO 1
#define FREQINIMIGOS 20
#define FREQNUKE 1
#define MOVIMENTACAOINIMIGOS 300
#define CHANCEINIMIGOTIRO 60 

void must_init(bool test, const char *description){
    if(test) return;

    printf("nao foi possivel iniciar: %s\n", description);
    exit(1);
}


void cria_barreiras(t_lista *l,tsprite sprite){
	int i;
	for (i = 0 ; i < 20 ; i++)
		must_init(insere_inicio_lista(sprite, i*32, 0 , 0 , l),"elemento lista barreira");
	for (i = 0 ; i < 20 ; i++)
		must_init(insere_inicio_lista(sprite, i*32 , 608 , 0, l),"elemento lista barreira");
	for (i = 1 ; i < 19; i++)
		must_init(insere_inicio_lista(sprite, 0 , i*32 , 0 , l),"elemento lista barreira");
	for (i = 1 ; i < 19; i++)
		must_init(insere_inicio_lista(sprite, 608 , i*32 , 0 , l),"elemento lista barreira");
} 

void cria_agua(t_lista *l,tsprite sprite){
	int i;
	for (i = 9 ; i < 11 ; i++){
		must_init(insere_inicio_lista(sprite, 32 , i*32 ,0 ,l),"elemento lista barreira");
		must_init(insere_inicio_lista(sprite, 64 , i*32 ,0 ,l),"elemento lista barreira");

		must_init(insere_inicio_lista(sprite, 160 , i*32 ,0 ,l),"elemento lista barreira");
		must_init(insere_inicio_lista(sprite, 192 , i*32 ,0 ,l),"elemento lista barreira");

		must_init(insere_inicio_lista(sprite, 288 , i*32 ,0 ,l),"elemento lista barreira");
		must_init(insere_inicio_lista(sprite, 320 , i*32 ,0 ,l),"elemento lista barreira");

		must_init(insere_inicio_lista(sprite, 416 , i*32 ,0 ,l),"elemento lista barreira");
		must_init(insere_inicio_lista(sprite, 448 , i*32 ,0 ,l),"elemento lista barreira");
		
		must_init(insere_inicio_lista(sprite, 544 , i*32 ,0 ,l),"elemento lista barreira");
		must_init(insere_inicio_lista(sprite, 576 , i*32 ,0 ,l),"elemento lista barreira");
	}	

}

void cria_blocos(t_lista *l,tsprite sprite){
	int i;
	for (i = 0 ; i < 2 ; i++){
		must_init(insere_inicio_lista(sprite, 160+i*32, 128, 0, l),"elemento lista blocos");
		must_init(insere_inicio_lista(sprite, 416+i*32, 128, 0, l),"elemento lista blocos");
		must_init(insere_inicio_lista(sprite, 32+i*32 , 352, 0, l),"elemento lista blocos");
		must_init(insere_inicio_lista(sprite, 544+i*32, 352, 0, l),"elemento lista blocos");
	}
}

void cria_matos(t_lista *l,tsprite sprite){
	int i;
	for (i = 0 ; i < 2 ; i++){
		must_init(insere_inicio_lista(sprite, 160+i*32, 224, 0, l),"elemento lista matos");
		must_init(insere_inicio_lista(sprite, 160+i*32, 416, 0, l),"elemento lista matos");
		must_init(insere_inicio_lista(sprite, 160+i*32, 448, 0, l),"elemento lista matos");
		must_init(insere_inicio_lista(sprite, 416+i*32, 224, 0, l),"elemento lista matos");
		must_init(insere_inicio_lista(sprite, 416+i*32, 416, 0, l),"elemento lista matos");
		must_init(insere_inicio_lista(sprite, 416+i*32, 448, 0, l),"elemento lista matos");
	}
}

void cria_paredes(t_lista *l,tsprite sprite){
	int i;
	for (i = 0 ; i < 41 ; i++){
		if ((i>=4 && i<= 13) || (i>=28 && i<= 35)){
			must_init(insere_inicio_lista(sprite,64,i*16,0,l) ,"elemento lista parede");
			must_init(insere_inicio_lista(sprite,80,i*16,0,l) ,"elemento lista parede");
			must_init(insere_inicio_lista(sprite,544,i*16,0,l),"elemento lista parede");
			must_init(insere_inicio_lista(sprite,560,i*16,0,l),"elemento lista parede");
		}
		if ((i>=4 && i<=5) || (i>=34 && i<=35)){
			must_init(insere_inicio_lista(sprite,96,i*16,0,l) ,"elemento lista parede");
			must_init(insere_inicio_lista(sprite,112,i*16,0,l),"elemento lista parede");
			must_init(insere_inicio_lista(sprite,512,i*16,0,l),"elemento lista parede");
			must_init(insere_inicio_lista(sprite,528,i*16,0,l),"elemento lista parede");
		}
		if ((i>=4 && i<=5)|| (i>=34 && i<=35) || (i>=8 && i<=9)){
			must_init(insere_inicio_lista(sprite,128,i*16,0,l),"elemento lista parede");
			must_init(insere_inicio_lista(sprite,144,i*16,0,l),"elemento lista parede");
			must_init(insere_inicio_lista(sprite,496,i*16,0,l),"elemento lista parede");
			must_init(insere_inicio_lista(sprite,480,i*16,0,l),"elemento lista parede");
		}
		if ((i>=10 && i<=13)|| (i>=30 && i<=31) || (i>=34 && i<=35)){
			must_init(insere_inicio_lista(sprite,160,i*16,0,l),"elemento lista parede");
			must_init(insere_inicio_lista(sprite,176,i*16,0,l),"elemento lista parede");
			must_init(insere_inicio_lista(sprite,464,i*16,0,l),"elemento lista parede");
			must_init(insere_inicio_lista(sprite,448,i*16,0,l),"elemento lista parede");
		}
		if ((i>=10 && i<=13) || (i>=30 && i<=31)){
			must_init(insere_inicio_lista(sprite,192,i*16,0,l),"elemento lista parede");
			must_init(insere_inicio_lista(sprite,208,i*16,0,l),"elemento lista parede");
			must_init(insere_inicio_lista(sprite,432,i*16,0,l),"elemento lista parede");
			must_init(insere_inicio_lista(sprite,416,i*16,0,l),"elemento lista parede");
		}
		if ((i>=4 && i<=5) || (i>=8 && i<=9) || (i>=30 && i<=31)){
			must_init(insere_inicio_lista(sprite,224,i*16,0,l),"elemento lista parede");
			must_init(insere_inicio_lista(sprite,240,i*16,0,l),"elemento lista parede");
			must_init(insere_inicio_lista(sprite,384,i*16,0,l),"elemento lista parede");
			must_init(insere_inicio_lista(sprite,400,i*16,0,l),"elemento lista parede");
		}	
		if ((i>=4 && i<=5) || (i>=30 && i<=31)){
			must_init(insere_inicio_lista(sprite,256,i*16,0,l),"elemtento lista parede");
			must_init(insere_inicio_lista(sprite,272,i*16,0,l),"elemtento lista parede");
			must_init(insere_inicio_lista(sprite,368,i*16,0,l),"elemtento lista parede");
			must_init(insere_inicio_lista(sprite,352,i*16,0,l),"elemtento lista parede");
		}
		if ((i>=30 && i<=31) || (i>=22 && i<=25)){
			must_init(insere_inicio_lista(sprite,288,i*16,0,l),"elemtento lista parede");
			must_init(insere_inicio_lista(sprite,304,i*16,0,l),"elemtento lista parede");
			must_init(insere_inicio_lista(sprite,320,i*16,0,l),"elemtento lista parede");
			must_init(insere_inicio_lista(sprite,336,i*16,0,l),"elemtento lista parede");
		}
		if 	((i>=8 && i<=17) || (i>=34 && i<=35)){
			must_init(insere_inicio_lista(sprite,320,i*16,0,l),"elemtento lista parede");
			must_init(insere_inicio_lista(sprite,304,i*16,0,l),"elemtento lista parede");
		}
		if 	((i>=4 && i<=5) || (i>=34 && i<=37)){
			must_init(insere_inicio_lista(sprite,336,i*16,0,l),"elemtento lista parede");
			must_init(insere_inicio_lista(sprite,288,i*16,0,l),"elemtento lista parede");
		}
		if 	(i>=34 && i<=37){
			must_init(insere_inicio_lista(sprite,352,i*16,0,l),"elemtento lista parede");
			must_init(insere_inicio_lista(sprite,272,i*16,0,l),"elemtento lista parede");
		}
		if (i>=8 && i<=9){
			must_init(insere_inicio_lista(sprite,368,i*16,0,l),"elemtento lista parede");
			must_init(insere_inicio_lista(sprite,256,i*16,0,l),"elemtento lista parede");
		}
	}	
}

void cria_jogador(t_lista *l, int x, int y,tsprite sprite){
	must_init(insere_inicio_lista(sprite, x, y, 0, l),"inserir jogador lista");
}

void atualiza_jogador(t_lista *l ,int x, int y, int dir,tsprite sprite){
	inicializa_atual_inicio(l);
	modifica_item_atual(sprite, x, y ,dir ,l);
}

void inicia_sprite(tsprite *sprite,int lin ,int col,int ver, int versao){
	float dir = 1.57;
	if (versao == 1)
		al_draw_scaled_rotated_bitmap(sprite->corpo1,14, 14, lin, col, 1, 1, dir*ver, 0);
	else if (versao == 2)
		al_draw_scaled_rotated_bitmap(sprite->corpo2,14, 14, lin, col, 1, 1, dir*ver, 0);
}

void imprime_tanks(t_lista *l, int versao){
	int tam,i,lin,col,dir;
	tsprite s;  
	tamanho_lista(&tam,l);
	inicializa_atual_inicio(l);
	for (i = 0 ; i < tam ; i++){
		consulta_item_atual(&s,&lin,&col,&dir,l);
		inicia_sprite(&s ,lin,col,dir,versao);
		incrementa_atual(l);
	}
}

void imprime_tiros(t_lista *l,int R, int G, int B){
	int tam,i,lin,col,dir;
	tsprite s;  

	tamanho_lista(&tam,l);
	inicializa_atual_inicio(l);
	for (i = 0 ; i < tam ; i++){
		consulta_item_atual(&s,&lin,&col,&dir,l);
		al_draw_filled_circle(lin, col, 4, al_map_rgb(R, G, B));
		incrementa_atual(l);
	}
}

void cria_tiro(t_lista *l,int lin, int col, int dir,tsprite sprite){
	must_init(insere_inicio_lista(sprite, lin, col , dir ,l ),"iniciar tiro lista");
}


void atualiza_tiros(t_lista *l){
	int tam,i,lin,col,dir;
	tsprite s;  

	tamanho_lista(&tam,l);
	inicializa_atual_inicio(l);
	for (i = 0 ; i < tam ; i++){
		consulta_item_atual(&s,&lin,&col,&dir,l);
		switch(dir){
			case 0:
				modifica_item_atual(s,lin,col-=5,dir,l);
				break;
			case 1:
				modifica_item_atual(s,lin+=5,col,dir,l);
				break;
			case 2:
				modifica_item_atual(s,lin,col+=5,dir,l);
				break;
			case 3:
				modifica_item_atual(s,lin-=5,col,dir,l);
				break;
		}		
		if (lin < 32 || col < 32 || lin > 608 || col > 608)
			remove_item_atual(&s,&lin,&col,&dir,l);
		else
			incrementa_atual(l);
	}		
}

void inicia_sprite_ambiente(tsprite *sprite,int lin ,int col,int dir,int ver){
	if (ver == 1)
		al_draw_bitmap(sprite->corpo1,lin, col,0);	
	if (ver == 2)
		al_draw_bitmap(sprite->corpo2,lin, col,0);

}

void imprime_ambiente(t_lista *l,int ver){
	int tam,i,lin,col,dir;
	tsprite s;  

	tamanho_lista(&tam,l);
	inicializa_atual_inicio(l);
	for (i = 0 ; i < tam ; i++){
		consulta_item_atual(&s,&lin,&col,&dir,l);
		inicia_sprite_ambiente(&s ,lin,col,dir,ver);
		incrementa_atual(l);
	}
}

void cria_insignia(t_lista *l,tsprite sprite){
	must_init(insere_inicio_lista(sprite,304,576,0,l),"inserir insignia lista");
}

int colisao_tank_parede(t_lista *lista1,t_lista *lista2){
	int i, j, dir1, lin1, col1, dir2, lin2, col2;
	tsprite sprite1, sprite2;
	int tam1, tam2;
	tamanho_lista(&tam1,lista1);
	tamanho_lista(&tam2,lista2);
	inicializa_atual_inicio(lista1);
	for(i = 0 ; i < tam1 ; i++){
		consulta_item_atual(&sprite1,&lin1,&col1,&dir1,lista1);
		inicializa_atual_inicio(lista2);
		for (j = 0 ; j < tam2 ; j++){
			consulta_item_atual(&sprite2,&lin2,&col2,&dir2,lista2);
			if (((lin1-lin2) < 32 && (lin1-lin2) > -16) && ((col1-col2) < 32 && (col1-col2) > -16) ){
				return 1;
			}
			else {
				incrementa_atual(lista2);
			}
		}
		incrementa_atual(lista1);
	}
	return 0;	
}

int colisao_tank_bloco(t_lista *lista1,t_lista *lista2){
	int i, j, dir1, lin1, col1, dir2, lin2, col2;
	tsprite sprite1, sprite2;
	int tam1, tam2;
	tamanho_lista(&tam1,lista1);
	tamanho_lista(&tam2,lista2);
	inicializa_atual_inicio(lista1);
	for(i = 0 ; i < tam1 ; i++){
		consulta_item_atual(&sprite1,&lin1,&col1,&dir1,lista1);
		inicializa_atual_inicio(lista2);
		for (j = 0 ; j < tam2 ; j++){
			consulta_item_atual(&sprite2,&lin2,&col2,&dir2,lista2);
			if (((lin1-lin2) < 47 && (lin1-lin2) > -16) && ((col1-col2) < 47 && (col1-col2) > -16)){
				if (sprite1.invencivel == 0)
					return 1;
			}
			else {
				incrementa_atual(lista2);
			}
		}
		incrementa_atual(lista1);
	}
	return 0;	
}

int colisao_tiro_parede(t_lista *lista1,t_lista *lista2){
	int i, j, dir1, lin1, col1, dir2, lin2, col2;
	int teste;
	tsprite sprite1, sprite2;
	int tam1, tam2;
	tamanho_lista(&tam1,lista1);
	tamanho_lista(&tam2,lista2);
	inicializa_atual_inicio(lista1);
	for(i = 0 ; i < tam1 ; i++){
		teste = 0;
		consulta_item_atual(&sprite1,&lin1,&col1,&dir1,lista1);
		inicializa_atual_inicio(lista2);
		for (j = 0 ; j < tam2 ; j++){
			consulta_item_atual(&sprite2,&lin2,&col2,&dir2,lista2);
			if (((lin1-lin2) < 19 && (lin1-lin2) > -4) && ((col1-col2) < 19 && (col1-col2) > -4)){ //valores antigos 19 e -4
				remove_item_atual(&sprite1,&lin1,&col1,&dir1,lista1);
				remove_item_atual(&sprite2,&lin2,&col2,&dir2,lista2);
				teste = 1; 
				break;
			}
			else {
				incrementa_atual(lista2);
			}
		}
		if (!teste)
			incrementa_atual(lista1);
	}
	return 0;	
}

int colisao_tiro_bloco(t_lista *lista1,t_lista *lista2){
	int i, j, dir1, lin1, col1, dir2, lin2, col2;
	int teste;
	tsprite sprite1, sprite2;
	int tam1, tam2;
	tamanho_lista(&tam1,lista1);
	tamanho_lista(&tam2,lista2);
	inicializa_atual_inicio(lista1);
	for(i = 0 ; i < tam1 ; i++){
		teste = 0; 
		consulta_item_atual(&sprite1,&lin1,&col1,&dir1,lista1);
		inicializa_atual_inicio(lista2);
		for (j = 0 ; j < tam2 ; j++){
			consulta_item_atual(&sprite2,&lin2,&col2,&dir2,lista2);
			if (((lin1-lin2) < 35 && (lin1-lin2) > -4) && ((col1-col2) < 35 && (col1-col2) > -4) ){
				remove_item_atual(&sprite1,&lin1,&col1,&dir1,lista1);
				teste = 1;
				break;
			}
			else {
				incrementa_atual(lista2);
			}
		}
		if (!teste)
			incrementa_atual(lista1);
	}
	return 0;	
}


void inicia_nuke(t_lista *l,tsprite sprite){
	if (rand() % 10000 < FREQNUKE)
		must_init(insere_inicio_lista(sprite, 32 + (rand() % 576),32 + (rand() % 576), 0, l),"elemento nuke lista");
}


int colisao_criando_inimigo(int lin1,int col1,int tamlista,t_lista *l){
	int i, lin2,col2,dir2;
	tsprite sprite2;
	inicializa_atual_inicio(l);
	incrementa_atual(l);
	for(i = 1 ; i < tamlista ; i++){
		consulta_item_atual(&sprite2,&lin2,&col2,&dir2,l);
		if (((lin1-lin2) < 40 && (lin1-lin2) > -14) && ((col1-col2) < 40 && (col1-col2) > -14))
			return 1;
	incrementa_atual(l);
	}	
	return 0;
}

void inicia_inimigos(t_lista *l,tsprite sprite){
	int dir1, lin1, col1;
	tsprite sprite1;
	int tam1;
	if(rand() % 10000 < FREQINIMIGOS){
		must_init(insere_inicio_lista(sprite,48,48,rand() % 4,l),"inimigo lista");
		tamanho_lista(&tam1,l);
		if (colisao_criando_inimigo(48,48,tam1,l))
			remove_inicio_lista(&sprite1,&lin1,&col1,&dir1,l);
	}
	if(rand() % 10000 < FREQINIMIGOS){
		must_init(insere_inicio_lista(sprite,326,48,rand() % 4,l),"inimigo lista");
		tamanho_lista(&tam1,l);
		if (colisao_criando_inimigo(326,48,tam1,l))
			remove_inicio_lista(&sprite1,&lin1,&col1,&dir1,l);
	}
	if(rand() % 10000 < FREQINIMIGOS){
		must_init(insere_inicio_lista(sprite,592,48,rand() % 4,l),"inimigo lista");
		tamanho_lista(&tam1,l);
		if (colisao_criando_inimigo(592,48,tam1,l))
			remove_inicio_lista(&sprite1,&lin1,&col1,&dir1,l);
	}
}

void atualiza_inimigos(t_lista *l,t_lista *paredes,t_lista *blocos,t_lista *aguas){
	int dir, lin, col;
	tsprite sprite;
	int i, tam;
	t_lista auxiliar;
	inicializa_lista(&auxiliar);
	tamanho_lista(&tam,l);
	inicializa_atual_inicio(l);
	for (i = 0 ; i < tam ; i++){
		consulta_item_atual(&sprite,&lin,&col,&dir,l);
		insere_inicio_lista(sprite,lin,col,dir,&auxiliar);
		inicializa_atual_inicio(&auxiliar);
		if (rand() % 10000 < MOVIMENTACAOINIMIGOS){
			dir = rand() % 4;
		}
		if(dir == 0){
			if( col > 48)
				modifica_item_atual(sprite,lin,col-=2,dir,&auxiliar);
			if(colisao_tank_parede(&auxiliar,paredes) || colisao_tank_bloco(&auxiliar,blocos) || colisao_tank_bloco(&auxiliar,aguas))
				modifica_item_atual(sprite,lin,col+=2,dir,&auxiliar);
		}
		else if(dir == 2){
			if( col < 592)
				modifica_item_atual(sprite,lin,col+=2,dir,&auxiliar);
			if(colisao_tank_parede(&auxiliar,paredes) || colisao_tank_bloco(&auxiliar,blocos) || colisao_tank_bloco(&auxiliar,aguas))
				modifica_item_atual(sprite,lin,col-=2,dir,&auxiliar);
		}
		else if(dir == 3){
			if( lin > 48)
				modifica_item_atual(sprite,lin-=2,col,dir,&auxiliar);
			if(colisao_tank_parede(&auxiliar,paredes) || colisao_tank_bloco(&auxiliar,blocos) || colisao_tank_bloco(&auxiliar,aguas))
				modifica_item_atual(sprite,lin+=2,col,dir,&auxiliar);
		}
		else if(dir == 1){
			if( lin < 592)
				modifica_item_atual(sprite,lin+=2,col,dir,&auxiliar);
			if(colisao_tank_parede(&auxiliar,paredes) || colisao_tank_bloco(&auxiliar,blocos) || colisao_tank_bloco(&auxiliar,aguas))
				modifica_item_atual(sprite,lin-=2,col,dir,&auxiliar);
			}
		modifica_item_atual(sprite,lin,col,dir,l);	
		incrementa_atual(l);
	}
	destroi_lista(&auxiliar);
}

void inicia_bombas(t_lista *l,t_lista *lista1,tsprite sprite){
	int dir, lin, col;
	tsprite sprite1;
	int i, tam;
	tamanho_lista(&tam,l);
	inicializa_atual_inicio(l);
	for (i = 0 ; i < tam ; i++){
		consulta_item_atual(&sprite1,&lin,&col,&dir,l);
		if (rand() % 10000 < CHANCEINIMIGOTIRO){
			cria_tiro(lista1,lin,col,dir,sprite);
		}
	incrementa_atual(l);	
	}	
}


int colisao_tank_tiro(t_lista *lista1, t_lista *lista2){
	int i, j, dir1, lin1, col1, dir2, lin2, col2;
	int teste, teste2 = 0;	
	tsprite sprite1, sprite2;
	int tam1, tam2;
	tamanho_lista(&tam1,lista1);
	tamanho_lista(&tam2,lista2);
	inicializa_atual_inicio(lista1);
	for(i = 0 ; i < tam1 ; i++){
		teste = 0;
		consulta_item_atual(&sprite1,&lin1,&col1,&dir1,lista1);
		inicializa_atual_inicio(lista2);
		for (j = 0 ; j < tam2 ; j++){
			consulta_item_atual(&sprite2,&lin2,&col2,&dir2,lista2);
			if (((lin1-lin2) < 18 && (lin1-lin2) > -18) && ((col1-col2) < 18 && (col1-col2) > -18)){ //valores antigos 19 e -4
				remove_item_atual(&sprite1,&lin1,&col1,&dir1,lista1);
				remove_item_atual(&sprite2,&lin2,&col2,&dir2,lista2);
				teste = 1; 
				teste2 = 1;
				break;
			}
			else {
				incrementa_atual(lista2);
			}
		}
		if (!teste)
			incrementa_atual(lista1);
	}
	return teste2;
}


























int main(){

	float angle = 0;
	float x, y;
    x = 320;
    y = 446;
    int cheatcode = 0; 

    must_init(al_init(), "allegro");
    must_init(al_init_image_addon(),"addon de imagems");
    must_init(al_init_primitives_addon(), "addon primitives");
    must_init(al_install_audio(),"intalacao de audio");
    must_init(al_init_acodec_addon(),"addon acodec");

    t_lista jogadores;
	t_lista inimigos;
	t_lista paredes;
	t_lista barreiras;
	t_lista aguas;
	t_lista matos;
	t_lista insignias;
	t_lista nukes;
	t_lista tiros;
	t_lista bombas;
	t_lista blocos;
	
	must_init(inicializa_lista(&jogadores),"lista jogador");
	must_init(inicializa_lista(&inimigos),"lista inimigos");
	must_init(inicializa_lista(&paredes),"lista paredes");
	must_init(inicializa_lista(&barreiras),"lista barreiras");
	must_init(inicializa_lista(&aguas),"lista aguas");
	must_init(inicializa_lista(&matos),"lista matos");
	must_init(inicializa_lista(&insignias),"lista insignia");
	must_init(inicializa_lista(&nukes),"lista nukes");
	must_init(inicializa_lista(&tiros),"lista tiros");
	must_init(inicializa_lista(&bombas),"lista bombas");
	must_init(inicializa_lista(&blocos),"lista blocos");

	ALLEGRO_BITMAP* spritejogador1 = al_load_bitmap(SPRITEJOGADOR1);
	ALLEGRO_BITMAP* spritejogador2 = al_load_bitmap(SPRITEJOGADOR2);
	ALLEGRO_BITMAP* spriteinimigo1 = al_load_bitmap(SPRITEINIMIGO1);
	ALLEGRO_BITMAP* spriteparede = al_load_bitmap(SPRITEPAREDE);
	ALLEGRO_BITMAP* spritebarreira = al_load_bitmap(SPRITEBARREIRA);
	ALLEGRO_BITMAP* spritepreenchimento = NULL;
	ALLEGRO_BITMAP* spriteagua = al_load_bitmap(SPRITEAGUA);
	ALLEGRO_BITMAP* spritemato = al_load_bitmap(SPRITEMATO);
	ALLEGRO_BITMAP* spritebloco = al_load_bitmap(SPRITEBLOCO);
	ALLEGRO_BITMAP* spriteinsignia = al_load_bitmap(SPRITEINSGINIA);
	ALLEGRO_BITMAP* spritenuke  = al_load_bitmap(SPRITENUKE);

	must_init(spritejogador1,"sprite jogador1");
	must_init(spritejogador2,"sprite jogador2");
	must_init(spriteinimigo1,"sprite jogador");
	must_init(spriteparede,"sprite jogador");
	must_init(spritebarreira,"sprite jogador");
	must_init(spriteagua,"sprite jogador");
	must_init(spritemato,"sprite jogador");
	must_init(spritebloco,"sprite jogador");
	must_init(spriteinsignia,"sprite jogador");
	must_init(spritenuke,"sprite jogador");

	tsprite jogador = {32,32,spritejogador1,spritejogador2,spritejogador1,cheatcode};
	tsprite inimigo = {32,32,spriteinimigo1,spriteinimigo1,spriteinimigo1,0};
	tsprite parede = {16,16,spriteparede,spriteparede,spriteparede,0};
	tsprite barreira = {32,32,spritebarreira,spritebarreira,spritebarreira,1};
	tsprite preenchimento = {4,4,spritepreenchimento,spritepreenchimento,spritepreenchimento,0};
	tsprite agua = {32,32,spriteagua,spriteagua,spriteagua,0};
	tsprite mato = {32,32,spritemato,spritemato,spritemato,0};
	tsprite bloco = {16,16,spritebloco,spritebloco,spritebloco,1};
	tsprite insignia = {32,32,spriteinsignia,spriteinsignia,spriteinsignia,0};
	tsprite nuke = {32,32,spritenuke,spritenuke,spritenuke,0};

	ALLEGRO_SAMPLE* somtiro ; 
	ALLEGRO_SAMPLE* sommorteinimigo;
	ALLEGRO_SAMPLE* somnuke;

	cria_jogador(&jogadores, x, y,jogador);
	cria_barreiras(&barreiras,barreira);
  	cria_agua(&aguas,agua);
  	cria_blocos(&blocos,bloco);
  	cria_matos(&matos,mato);
  	cria_paredes(&paredes,parede);
  	cria_insignia(&insignias,insignia);

  	int pontuacao = 12;
  	int ver = 1; 
  	int time = 1; 

  	al_reserve_samples(2);

  	somtiro = al_load_sample("resources/somtiro.ogg");
  	must_init(somtiro,"som tiro");
    
    must_init(al_install_keyboard(), "keyboard");
  
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    ALLEGRO_DISPLAY* disp = al_create_display(800, 640);
    must_init(disp, "display");

    ALLEGRO_FONT* font = al_create_builtin_font();
    must_init(font, "font");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    ALLEGRO_KEYBOARD_STATE ks;

    al_start_timer(timer);
    int tam_tiros = 0;

    while(1){
        al_wait_for_event(queue, &event);
        al_clear_to_color(al_map_rgb(30, 30, 30));

        inicia_nuke(&nukes,nuke);
        inicia_inimigos(&inimigos,inimigo);
        atualiza_tiros(&tiros);
        inicia_bombas(&inimigos,&bombas,preenchimento);
        atualiza_inimigos(&inimigos,&paredes,&blocos,&aguas);
		atualiza_tiros(&bombas);
		colisao_tiro_parede(&tiros,&paredes); 
		colisao_tiro_bloco(&tiros,&blocos);
		colisao_tiro_parede(&bombas,&paredes);
		colisao_tiro_bloco(&bombas,&blocos);
		tamanho_lista(&tam_tiros,&tiros);
		colisao_tank_tiro(&inimigos,&tiros);

        switch(event.type){
            case ALLEGRO_EVENT_TIMER:
                al_get_keyboard_state(&ks);
				if(al_key_down(&ks, ALLEGRO_KEY_UP)){
					angle = 0;
					if( y > 48)
						y-=2;
					atualiza_jogador(&jogadores,x,y,angle,jogador);
					if(colisao_tank_parede(&jogadores,&paredes) || colisao_tank_bloco(&jogadores,&blocos))
					    y+=2;
				}
				else if(al_key_down(&ks, ALLEGRO_KEY_DOWN)){
					angle = 2;
					if( y < 592)
						y+=2;
					atualiza_jogador(&jogadores,x,y,angle,jogador);
					if(colisao_tank_parede(&jogadores,&paredes) || colisao_tank_bloco(&jogadores,&blocos))
					    y-=2;
				}
				else if(al_key_down(&ks, ALLEGRO_KEY_LEFT)){
					angle = 3;
					if( x > 48)
						x-=2;
					atualiza_jogador(&jogadores,x,y,angle,jogador);
					if(colisao_tank_parede(&jogadores,&paredes) || colisao_tank_bloco(&jogadores,&blocos))
					    x+=2;
				}
				else if(al_key_down(&ks, ALLEGRO_KEY_RIGHT)){
					angle = 1;
					if( x < 592)
						x+=2;
					atualiza_jogador(&jogadores,x,y,angle,jogador);
					if(colisao_tank_parede(&jogadores,&paredes) || colisao_tank_bloco(&jogadores,&blocos))
					    x-=2;
				}
				if(al_key_down(&ks, ALLEGRO_KEY_SPACE) && LIMITETIRO > tam_tiros ){
					al_play_sample(somtiro,1,0,1,ALLEGRO_PLAYMODE_ONCE,NULL);
					cria_tiro(&tiros,x,y,angle,preenchimento);
				} 
				if(al_key_down(&ks, ALLEGRO_KEY_ESCAPE))
					done = true;
				redraw = true;
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }
        
        if(done)
            break;

        done = colisao_tank_bloco(&jogadores,&aguas);
        if(done)
            break;

        if(redraw && al_is_event_queue_empty(queue)){
    		if (time  == 1)
    			ver = 1;
    		else if (time == 60)
    			ver = 2; 
            imprime_ambiente(&barreiras,ver);
            imprime_ambiente(&aguas,ver);
            imprime_ambiente(&blocos,ver);
            imprime_ambiente(&paredes,ver);
            imprime_ambiente(&insignias,ver);
            imprime_ambiente(&nukes,ver);
            imprime_tanks(&inimigos,ver);
            imprime_tiros(&tiros,0,255,255);
            imprime_tiros(&bombas,255,0,0);
            imprime_tanks(&jogadores,ver);
            al_draw_textf(font, al_map_rgb(255, 255, 255), 650 ,10, 0, "Pontuacao:");
            al_draw_textf(font, al_map_rgb(255, 255, 255), 655, 20, 0, "%i",pontuacao);
            imprime_ambiente(&matos,ver);
            al_flip_display();
            if (time == 120){
            	time = 0;
            }
            time++;
            redraw = false;
        }
    }

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_sample(somtiro);

    al_destroy_bitmap(spritejogador1);
    al_destroy_bitmap(spritejogador2);
    al_destroy_bitmap(spriteinimigo1);
    al_destroy_bitmap(spriteparede);
    al_destroy_bitmap(spritebarreira);
    al_destroy_bitmap(spriteagua);
    al_destroy_bitmap(spritemato);
    al_destroy_bitmap(spriteinsignia);
    al_destroy_bitmap(spritenuke);

    destroi_lista(&jogadores);
	destroi_lista(&inimigos);
	destroi_lista(&paredes);
	destroi_lista(&barreiras);
	destroi_lista(&aguas);
	destroi_lista(&matos);
	destroi_lista(&insignias);
	destroi_lista(&nukes);
	destroi_lista(&tiros);
	destroi_lista(&bombas);
	destroi_lista(&blocos);

    return 0;
}
