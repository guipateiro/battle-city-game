//GRR20197152 Guilherme Costa Pateiro
//Universidade Federal do Parana , programacao2 - ERE2 A
//ultima edicao: 9/12/2020 19:36
#include "macrojogo.h"
#include <stdio.h>


int main(){

	must_init(al_init(), "allegro"); 							//inicia o allegro 
	must_init(al_init_image_addon(),"addon de imagems");		//inicia o plugin de imagens do allegro 
	ALLEGRO_DISPLAY* display1 = al_create_display(800, 640);	//cria o display
    must_init(display1, "display"); 							//verifica se o display foi criado 

    int cheat = 0;   		//verifica se o jogo vai comecar normalmente ou com com o cheatmode 
    int continuar = 1; 		//garante o loop de reinicializacao do jogo 
    int pontos;				//pontuacao do loop
    cheat = menuprincipal(display1);  //menu principal 
    while (continuar){
		pontos = jogando(display1,cheat,continuar); //jogo em si
		if (pontos != -1)
			fimdejogo(display1,pontos,&continuar); //tela de fim de jogo, carregamento das pontuacoes
		else
			continuar = 0;
	}
	al_destroy_display(display1); 	//destroi o display 
	return 0;

}