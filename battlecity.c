
#include "macrojogo.h"
//#include "jogo.h"
//#include "liblista.h"
#include <stdio.h>


int main(){

	must_init(al_init(), "allegro");
	must_init(al_init_image_addon(),"addon de imagems");
	ALLEGRO_DISPLAY* display1 = al_create_display(800, 640);
    must_init(display1, "display");

    int cheat = 0;
    int continuar = 1;
    int pontos;
    cheat = menuprincipal(display1);
    while (continuar){
        printf("iniciando jogo \n");
		pontos = jogando(display1,cheat,continuar);
		if (pontos != -1)
			fimdejogo1(display1,pontos,&continuar);
		else
			continuar = 0;
        printf("%i \n",continuar);
	}
	return 0;

}