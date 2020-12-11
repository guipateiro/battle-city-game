//GRR20197152 Guilherme Costa Pateiro
//Universidade Federal do Parana , programacao2 - ERE2 A
//ultima edicao: 9/12/2020 19:41
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_ttf.h>
#include "liblista.h"
#include "jogo.h"


//verifica se uma variavel foi iniciada, parando o programa q escrevendo o erro em stdout
void must_init(bool test, const char *description){
    if(test) return;

    printf("nao foi possivel iniciar: %s\n", description);
    exit(1);
}

//--------------------------------------------------------------------------------
//                       AREA DE CRIACAO DE OBJETOS
//--------------------------------------------------------------------------------
//basicamente insere na lista os sprites em  uma lista 


//cria todas as barreiras, em caso de erro, para o programa 
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

//cria todas as aguas, em caso de erro, para o programa 
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

//cria todos os blocos, em caso de erro, para o programa 
void cria_blocos(t_lista *l,tsprite sprite){
	int i;
	for (i = 0 ; i < 2 ; i++){
		must_init(insere_inicio_lista(sprite, 160+i*32, 128, 0, l),"elemento lista blocos");
		must_init(insere_inicio_lista(sprite, 416+i*32, 128, 0, l),"elemento lista blocos");
		must_init(insere_inicio_lista(sprite, 32+i*32 , 352, 0, l),"elemento lista blocos");
		must_init(insere_inicio_lista(sprite, 544+i*32, 352, 0, l),"elemento lista blocos");
	}
}

//cria todos os matos, em caso de erro, para o programa 
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

//cria todas as paredes, em caso de erro, para o programa 
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

//cria todas as aguas, em caso de erro, para o programa 
void cria_jogador(t_lista *l, int x, int y,tsprite sprite){
	must_init(insere_inicio_lista(sprite, x, y, 0, l),"inserir jogador lista");
}

//cria todas as aguas, em caso de erro, para o programa 
void cria_tiro(t_lista *l,int lin, int col, int dir,tsprite sprite){
	must_init(insere_inicio_lista(sprite, lin, col , dir ,l ),"iniciar tiro lista");
}

//cria todas as aguas, em caso de erro, para o programa 
void cria_insignia(t_lista *l,tsprite sprite){
	must_init(insere_inicio_lista(sprite,304,576,0,l),"inserir insignia lista");
}

//cria todas as aguas, em caso de erro, para o programa 
void atualiza_jogador(t_lista *l ,int x, int y, int dir,tsprite sprite){
	inicializa_atual_inicio(l);
	modifica_item_atual(sprite, x, y ,dir ,l);
}

//cria nukes, em caso de erro, para o programa 
void inicia_nuke(t_lista *l,tsprite sprite){
	if (rand() % 10000 < FREQNUKE)
		must_init(insere_inicio_lista(sprite, 32 + (rand() % 576),32 + (rand() % 576), 0, l),"elemento nuke lista");
}

//se um tank for criado onde ja tem um tank, retorna 1, caso contrario, retorna 0
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

//cria inimigos, em caso de erro, para o programa 
//caso um inimigo seja criado onde ja tem um inimigo, cancela a criacao 
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

//cria bombas a partir dos elementos de outra lista, em caso de erro, para o programa
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


//-------------------------------------------------------------------
//                          AREA DE COLISOES 
//-------------------------------------------------------------------

/* PSEUDOCODIGO GENERICO 
	funcao(lista1,lista2)
	INICIO 
	declara variaveis 
	descobre o tamanho de cada lista
	percorre listas1 
		pega elemento lista 1
		percorre lista 2
		pega elemento lista 2
			verifica colisao pora caixa
			toma uma decisao
		incrementa lista2
	incrementa lista1

*/

//verifica e houve uma colisao entre 2 listas 
//caso tenha uma colisao retorna 1, caso contrario retorna 0 
//a comparacao deve ocorer entre 1 sprite de 14 pixel centrelizado se outro de 16 pixels de tamanho total 
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

//verifica e houve uma colisao entre 2 listas 
//caso tenha uma colisao retorna 1, caso contrario retorna 0 
//a comparacao deve ocorer entre 1 sprite de 14 pixel centrelizado se outro de 32 pixels de tamanho total 
//caso o sprite da lista 1 seja invencivel sempre ratornara 0
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

//verifica e houve uma colisao entre 2 listas 
//caso tenha uma colisao retorna 1, caso contrario retorna 0 
//a comparacao deve ocorer entre 1 sprite de 14 pixel centrelizado se outro de 32 pixels de tamanho total 
int colisao_tank_bloco2(t_lista *lista1,t_lista *lista2){
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

//verifica e houve uma colisao entre 2 listas 
//caso haja uma colisao, ambos os elementos da lista sao removidos
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
		tamanho_lista(&tam2,lista2);
		for (j = 0 ; j < tam2 ; j++){
			consulta_item_atual(&sprite2,&lin2,&col2,&dir2,lista2);
			if (((lin1-lin2) < 19 && (lin1-lin2) > -4) && ((col1-col2) < 19 && (col1-col2) > -4)){ 
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

//verifica e houve uma colisao entre 2 listas 
//caso haja uma colisao, ambos os elementos da lista sao removidos
//retorna 1 caso tenha havido uma colisao 0 caso contrario 
int colisao_tiro_bloco(t_lista *lista1,t_lista *lista2){
	int i, j, dir1, lin1, col1, dir2, lin2, col2;
	int teste ,teste2 = 0;
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

//verifica e houve uma colisao entre 2 listas 
//caso haja uma colisao, ambos os elementos da lista sao removidos
//caso haja uma colisao, insere um elemento na lista 3 com o sprite 3
//retorna o numero de colisoes que ocorreram
int colisao_tank_tiro(t_lista *lista1, t_lista *lista2,t_lista *lista3,tsprite sprite3){
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
			if (((lin1-lin2) < 18 && (lin1-lin2) > -18) && ((col1-col2) < 18 && (col1-col2) > -18)){
				if(sprite1.invencivel == 1)
					return 0;
				remove_item_atual(&sprite1,&lin1,&col1,&dir1,lista1);
				remove_item_atual(&sprite2,&lin2,&col2,&dir2,lista2);
				insere_inicio_lista(sprite3,lin1,col1,dir1,lista3);
				teste = 1; 
				teste2 ++;
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

//verifica e houve uma colisao entre 2 listas 
//caso haja uma colisao, todos os elementos da lista 2 e lista 3 sao removidos 
//retorna o numero de elementos removidos da lista 3
int colisao_tank_nuke(t_lista *lista1,t_lista *lista2,t_lista *lista3){
	int tam3;
	tam3 = 0;
	if (colisao_tank_bloco2(lista1,lista2)){
		tamanho_lista(&tam3,lista3);
		esvazia_lista(lista3);
		esvazia_lista(lista2);
	}
	return tam3;
}

//---------------------------------------------------------------
//					AREA DE MOVIMENTACAO
//---------------------------------------------------------------

//atualiza a movimentacao dos inimigos
//se baseia na direcao atual do inimigo
//puequena chance de mudar a direcao do inimigo quando ele for atualizado
//verifica a calisao entre os inimigo e todos os blocos que impedem a movimentacao
//impede que os inimigo morram para agua 
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


//movimenta os tiros
//se baseia na direcao que ele esta 
//somente movimenta elementos em linha reta 
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


//---------------------------------------------------------------
//				AREA DE IMPRESSAO 
//---------------------------------------------------------------

//imprime vidas no canto da tela, se baseia no munero V (numero de vidas)
void imprime_vidas(int v,tsprite sprite,int ver){
	int i;

	for(i = 0 ; i < v ; i++){
		if (ver == 1)
		al_draw_bitmap(sprite.corpo1,675+i*32, 400,0);	
	if (ver == 2)
		al_draw_bitmap(sprite.corpo2,675+i*32, 400,0);
	}

}


//imprime ,em lin/col,uma lista
//percorre uma lista imprimindo 
//a cada frame, incremeta  um contador em cada elemento da lista, quando o contador chegar em 5, o elemento sai da lista 
void imprime_explosoes(t_lista *lista1){
	int tam,i,lin,col,dir;
	tsprite s;  

	tamanho_lista(&tam,lista1);
	inicializa_atual_inicio(lista1);
	for (i = 0 ; i < tam ; i++){
		consulta_item_atual(&s,&lin,&col,&dir,lista1);
		if (s.invencivel < 5){
			al_draw_bitmap(s.corpo1,lin-14,col-14,0);
			s.invencivel++;
			modifica_item_atual(s,lin,col,dir,lista1);
			incrementa_atual(lista1);
		}
		else 
			remove_item_atual(&s,&lin,&col,&dir,lista1);
	}
}

//imprime na tela, em lin/col um sprite
//o sprite que vai ser imprido se baseia em ver 
void inicia_sprite_ambiente(tsprite *sprite,int lin ,int col,int dir,int ver){
	if (ver == 1)
		al_draw_bitmap(sprite->corpo1,lin, col,0);	
	if (ver == 2)
		al_draw_bitmap(sprite->corpo2,lin, col,0);

}

//percorre uma lista, imprimindo todos os elementos dela
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

//imprime na tela, em lin/col um sprite
//o sprite que vai ser imprido se baseia em versao
//a direcao depende de ver
void inicia_sprite(tsprite *sprite,int lin ,int col,int ver, int versao){
	float dir = 1.57;
	if (versao == 1)
		al_draw_scaled_rotated_bitmap(sprite->corpo1,14, 14, lin, col, 1, 1, dir*ver, 0);
	else if (versao == 2)
		al_draw_scaled_rotated_bitmap(sprite->corpo2,14, 14, lin, col, 1, 1, dir*ver, 0);
}

//percorre uma lista de tanks, imprimindo todos elementos 
//a direcao de um sprite se baseiem dir 
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

//percorre uma lista, porem a unica parte utilizada sao lin/col 
//imprime uma circulo lo local de lin/col 
//a cor do circulo se baseia em R G B 
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
