

#include <allegro5/allegro_ttf.h>
#include "liblista.h"
#include "jogo.h"
#include "macrojogo.h"




int menuprincipal(ALLEGRO_DISPLAY* disp){

	must_init(al_init_primitives_addon(), "addon primitives");
    must_init(al_install_audio(),"intalacao de audio");
    must_init(al_init_acodec_addon(),"addon acodec");
    must_init(al_init_font_addon(),"addon fonte");
    must_init(al_init_ttf_addon(),"addon ttf fonte");
    must_init(al_install_keyboard(), "teclado");

    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_FONT* fontepixelar = al_load_font(FONTEPIXELAR,70,0);
    ALLEGRO_FONT* fontepixelar2 = al_load_font(FONTEPIXELAR, 32,0);
    must_init(font,"fonte");
    must_init(fontepixelar,"fonte pixelar");
    must_init(fontepixelar2,"fonte pixelar2");

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool done = false;
    bool redraw = true;
    bool jogar = false;
    ALLEGRO_EVENT event;
    int cheatcode;

    ALLEGRO_KEYBOARD_STATE ks;
    al_start_timer(timer);

    while(1){
        al_wait_for_event(queue, &event);
        al_clear_to_color(al_map_rgb(30, 30, 30));

        switch(event.type){
            case ALLEGRO_EVENT_TIMER:
                al_get_keyboard_state(&ks);			
                if(al_key_down(&ks, ALLEGRO_KEY_ENTER)){
                	cheatcode = 0;
                	jogar = true;
                }
				else if(al_key_down(&ks, ALLEGRO_KEY_F11)){
					cheatcode = 1;
					jogar = true; 
				}
				else if(al_key_down(&ks, ALLEGRO_KEY_ESCAPE)){
					done = true;	
				}
				redraw = true;
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }
        
        if(done)
            exit(0);

        if(jogar)
        	break;

        if(redraw && al_is_event_queue_empty(queue)){
            al_draw_textf(fontepixelar, al_map_rgb(255, 70, 0),400, 100 ,ALLEGRO_ALIGN_CENTER, "BATTLECITY");
            al_draw_textf(fontepixelar2, al_map_rgb(255, 128, 0),400, 300 ,ALLEGRO_ALIGN_CENTER, "[ENTER] PARA INICIAR");
            al_draw_textf(fontepixelar2, al_map_rgb(255, 128, 0),400, 350 ,ALLEGRO_ALIGN_CENTER, "[ESC] PARA SAIR");
           	
            al_flip_display();
            redraw = false;
        }
	}
    al_destroy_font(font);
    al_destroy_font(fontepixelar);
    al_destroy_font(fontepixelar2);

    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return cheatcode;
}
















int jogando(ALLEGRO_DISPLAY* disp,int cheatcode, int continuar){

	float angle = 0;
	float x, y;
    x = 320;
    y = 446;
    float timelast;
    float timenow;
    float numframes;
    int pontuacao = 0;
    int ver = 1; 
    int time = 1; 
    int help = 0;
    float m_FPS = 0;
    int pause = 0;
    int info = 0;
    int auxiliar1 = 0;
    int auxiliar2 = 0;
    int tam_tiros = 0;
    int jogo1 =0; 
    int vida = 3;
    int water = 0;
    bool done = false;
    bool redraw = true;


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
	t_lista explosoes;
	
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
	must_init(inicializa_lista(&explosoes),"lista explosoes");

	ALLEGRO_BITMAP* spritejogador1 = al_load_bitmap(SPRITEJOGADOR1);
	ALLEGRO_BITMAP* spritejogador2 = al_load_bitmap(SPRITEJOGADOR2);
	ALLEGRO_BITMAP* spriteinimigo1 = al_load_bitmap(SPRITEINIMIGO1);
	ALLEGRO_BITMAP* spriteparede = al_load_bitmap(SPRITEPAREDE);
	ALLEGRO_BITMAP* spritebarreira = al_load_bitmap(SPRITEBARREIRA);
	ALLEGRO_BITMAP* spritepreenchimento = NULL;
	ALLEGRO_BITMAP* spriteagua = al_load_bitmap(SPRITEAGUA);
	ALLEGRO_BITMAP* spritemato1 = al_load_bitmap(SPRITEMATO1);
	ALLEGRO_BITMAP* spritemato2 = al_load_bitmap(SPRITEMATO2);
	ALLEGRO_BITMAP* spritebloco = al_load_bitmap(SPRITEBLOCO);
	ALLEGRO_BITMAP* spriteinsignia = al_load_bitmap(SPRITEINSGINIA);
	ALLEGRO_BITMAP* spritenuke1 = al_load_bitmap(SPRITENUKE1);
	ALLEGRO_BITMAP* spritenuke2 = al_load_bitmap(SPRITENUKE2);
	ALLEGRO_BITMAP* spriteexplosao = al_load_bitmap(SPRITEEXPLOSAO);
    ALLEGRO_BITMAP* imagemdesenvolvedor = al_load_bitmap(IMAGEMEU);
    ALLEGRO_BITMAP* scooby = al_load_bitmap(IMAGEMSCOOBY);

	must_init(spritejogador1,"sprite jogador1");
	must_init(spritejogador2,"sprite jogador2");
	must_init(spriteinimigo1,"sprite inimigo1");
	must_init(spriteparede,"sprite jogador");
	must_init(spritebarreira,"sprite jogador");
	must_init(spriteagua,"sprite jogador");
	must_init(spritemato1,"sprite mato1");
	must_init(spritemato2,"sprite mato2");
	must_init(spritebloco,"sprite jogador");
	must_init(spriteinsignia,"sprite jogador");
	must_init(spritenuke1,"sprite nuke1");
	must_init(spritenuke2,"sprite nuke2");
	must_init(spriteexplosao,"spriteexplosao");
    must_init(imagemdesenvolvedor,"imagem do autor");
    must_init(scooby,"imagem do scooby");

	tsprite jogador = {32,32,spritejogador1,spritejogador2,cheatcode};
	tsprite inimigo = {32,32,spriteinimigo1,spriteinimigo1,0};
	tsprite parede = {16,16,spriteparede,spriteparede,0};
	tsprite barreira = {32,32,spritebarreira,spritebarreira,1};
	tsprite preenchimento = {4,4,spritepreenchimento,spritepreenchimento,0};
	tsprite agua = {32,32,spriteagua,spriteagua,0};
	tsprite mato = {32,32,spritemato1,spritemato2,0};
	tsprite bloco = {16,16,spritebloco,spritebloco,1};
	tsprite insignia = {32,32,spriteinsignia,spriteinsignia,0};
	tsprite nuke = {32,32,spritenuke1,spritenuke2,0};
	tsprite explosao = {32,32,spriteexplosao,spriteexplosao,0};

  	ALLEGRO_FONT* captureit1 = al_load_font(FONTECAPTUREIT1,30,0);
  	ALLEGRO_FONT* captureit2 = al_load_font(FONTECAPTUREIT2,30,0);
  	ALLEGRO_FONT* font = al_create_builtin_font();
  	ALLEGRO_FONT* opensans = al_load_font(FONTEOPENSANS,20,0);

  	must_init(captureit1,"fonte captureit1");
  	must_init(captureit2,"fonte captureit2");
  	must_init(font, "fonte defaut");
  	must_init(opensans, "fonte opensans");

  	al_reserve_samples(4);

  	ALLEGRO_SAMPLE* somtiro = al_load_sample(SOMTIRO);
  	ALLEGRO_SAMPLE* sommorteinimigo = al_load_sample(SOMINIMIGOMORRE);
  	ALLEGRO_SAMPLE* somnuke = al_load_sample(SOMNUKE);
  	ALLEGRO_SAMPLE* somfundo = al_load_sample(SOMFUNDO);

  	must_init(somtiro,"som tiro");
	must_init(sommorteinimigo,"som morte inimigo");
  	must_init(somnuke,"som nuke");
  	must_init(somfundo,"som  de fundo fundo");
    
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    must_init(timer, "timer");
    al_start_timer(timer);

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    ALLEGRO_EVENT event;

    ALLEGRO_KEYBOARD_STATE ks;

    cria_jogador(&jogadores, x, y,jogador);
    cria_barreiras(&barreiras,barreira);
    cria_agua(&aguas,agua);
    cria_blocos(&blocos,bloco);
    cria_matos(&matos,mato);
    cria_paredes(&paredes,parede);
    cria_insignia(&insignias,insignia);

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    al_play_sample(somfundo,0.02,0,1,ALLEGRO_PLAYMODE_LOOP,NULL);

    while(vida >= 0){
        al_wait_for_event(queue, &event);
        al_clear_to_color(al_map_rgb(30, 30, 30));

        if (!pause){ 
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
			auxiliar2 = colisao_tank_tiro(&inimigos,&tiros,&explosoes,explosao);
			if (auxiliar2)
				al_play_sample(sommorteinimigo,1,0,1,ALLEGRO_PLAYMODE_ONCE,NULL);
			auxiliar1 = colisao_tank_nuke(&jogadores,&nukes,&inimigos);
			if (auxiliar1){
				al_play_sample(somnuke,1,0,1,ALLEGRO_PLAYMODE_ONCE,NULL);
				al_clear_to_color(al_map_rgb(255,0,0));
			}
			pontuacao = pontuacao + (auxiliar2 * PONTOSCANHAO);
			pontuacao = pontuacao + (auxiliar1 * PONTOSCANHAO);
			jogo1 = colisao_tank_tiro(&jogadores,&bombas,&explosoes,explosao);
			water = colisao_tank_bloco(&jogadores,&aguas);
		}

        switch(event.type){
            case ALLEGRO_EVENT_TIMER:
                al_get_keyboard_state(&ks);
				if(!pause){
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
				} 
				if(al_key_down(&ks,ALLEGRO_KEY_P)){
					if (pause == 1)
						pause = 0;
					else if (pause == 0)
						pause = 1;
				}
				if(al_key_down(&ks,ALLEGRO_KEY_H) ||  al_key_down(&ks,ALLEGRO_KEY_F1)){
					if (help == 0){
						help = 1;
						pause = 1;
					}	
					else if (help == 1){
						help = 0;
					} 
				}
                if(al_key_down(&ks,ALLEGRO_KEY_I)){
                    if (info == 0){
                        info = 1;
                        pause = 1;
                    }   
                    else if (info == 1){
                        info = 0;
                    } 
                }
				
				if(al_key_down(&ks, ALLEGRO_KEY_ESCAPE)){
					pontuacao = -1;
					done = true;
				}
				redraw = true;
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                pontuacao = -1;
                break;
        }
        
        if(done)
            break;

        water = colisao_tank_bloco(&jogadores,&aguas);
       
        if(jogo1 || water){
			vida --;       
        	esvazia_lista(&jogadores);
        	esvazia_lista(&bombas);
        	x = 320;
    		y = 446;
        	cria_jogador(&jogadores, x, y,jogador);

       	}
       	done = colisao_tiro_bloco(&bombas,&insignias);
       	if (done)
       		break;

        if(redraw && al_is_event_queue_empty(queue)){
    		if (!help && !info){
	    		if (time  == 1)
    				ver = 1;
    			else if (time == 60)
    				ver = 2; 

	        	timenow = al_get_time();
    	    	numframes = timenow-timelast;
        		m_FPS = 1/(numframes);
        		timelast = timenow;

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
	            imprime_explosoes(&explosoes);
	            al_draw_textf(captureit1, al_map_rgb(255, 255, 255), 655, 20, 0, "%i",pontuacao);
	            al_draw_textf(font, al_map_rgb(255, 255, 255), 655, 600, 0, "FPS: %.0f",m_FPS);
	            al_draw_textf(captureit2, al_map_rgb(255, 255, 255), 670, 360 , 0, "VIDAS:");
	            al_draw_textf(captureit1, al_map_rgb(255, 255, 255), 670 ,500 , 0, "(P)ause");
	            al_draw_textf(captureit1, al_map_rgb(255, 255, 255), 670 ,540 , 0, "(H)elp");
	            imprime_ambiente(&matos,ver);
	            imprime_vidas(vida,jogador,ver);

                if (cheatcode){
                    al_draw_textf(captureit1, al_map_rgb(255, 0, 0),655 ,100 , 0, "CHEAT");
                    al_draw_textf(captureit1, al_map_rgb(255, 0, 0),655 ,130 , 0, "ATIVO");
	            }

	            if (pause){
	            	al_draw_textf(captureit1, al_map_rgb(255, 255, 255),260 ,250 , 0, "(P)ause");
	            }
            	if (time == 120){
            		time = 0;
            	}
            	time++;
            }	
            else if (info){
                // tela de creditos
            }
            else{
            	al_draw_textf(captureit1, al_map_rgb(255, 255, 255),400 ,20  ,ALLEGRO_ALIGN_RIGHT, "HELP MENU");
            	al_draw_textf(captureit1, al_map_rgb(255, 255, 255),200 ,100 ,ALLEGRO_ALIGN_RIGHT, "JOGADOR");
            	al_draw_bitmap(spritejogador1,240, 100,0);
            	al_draw_textf(opensans, al_map_rgb(255, 255, 255),280 ,100 ,ALLEGRO_ALIGN_LEFT, "Seu personagem");
            	al_draw_textf(captureit1, al_map_rgb(255, 255, 255),200 ,140 ,ALLEGRO_ALIGN_RIGHT, "INIMIGOS");
            	al_draw_bitmap(spriteinimigo1,240, 140,0);
            	al_draw_textf(opensans, al_map_rgb(255, 255, 255),280 ,140 ,ALLEGRO_ALIGN_LEFT, "Sim, eles querem te destruir, ganhe ponto detruindo eles");
            	al_draw_textf(captureit1, al_map_rgb(255, 255, 255),200 ,180 ,ALLEGRO_ALIGN_RIGHT, "PAREDES");
            	al_draw_bitmap(spriteparede,240, 180,0);
            	al_draw_textf(opensans, al_map_rgb(255, 255, 255),280 ,180 ,ALLEGRO_ALIGN_LEFT, "Ninguem pode passar, mas tiros podem quebrar");
            	al_draw_textf(captureit1, al_map_rgb(255, 255, 255),200 ,220 ,ALLEGRO_ALIGN_RIGHT, "BLOCOS");
            	al_draw_bitmap(spritebloco,240, 220,0);
            	al_draw_textf(opensans, al_map_rgb(255, 255, 255),280 ,220 ,ALLEGRO_ALIGN_LEFT, "Ninguem pode passar");
            	al_draw_textf(captureit1, al_map_rgb(255, 255, 255),200 ,260 ,ALLEGRO_ALIGN_RIGHT, "MATOS");
            	al_draw_bitmap(spritemato1,240, 260,0);
            	al_draw_textf(opensans, al_map_rgb(255, 255, 255),280 ,260 ,ALLEGRO_ALIGN_LEFT, "Dificulta a visao do que esta embaixo");
            	al_draw_textf(captureit1, al_map_rgb(255, 255, 255),200 ,300 ,ALLEGRO_ALIGN_RIGHT, "NUKES");
            	al_draw_bitmap(spritenuke1,240, 300,0);
            	al_draw_textf(opensans, al_map_rgb(255, 255, 255),280 ,300 ,ALLEGRO_ALIGN_LEFT, "Toque com seu tank para destruir todos os inimigos");
            	al_draw_textf(captureit1, al_map_rgb(255, 255, 255),200 ,340 ,ALLEGRO_ALIGN_RIGHT, "AGUAS");
            	al_draw_bitmap(spriteagua,240, 340,0);
            	al_draw_textf(opensans, al_map_rgb(255, 255, 255),280, 340 ,ALLEGRO_ALIGN_LEFT, "Seu tank nao sabe nadar, melhor nao tocar");

            	al_draw_textf(opensans, al_map_rgb(255, 255, 255),70 ,400 ,ALLEGRO_ALIGN_LEFT, "Utilize as setas para andar");
            	al_draw_textf(opensans, al_map_rgb(255, 255, 255),70 ,430 ,ALLEGRO_ALIGN_LEFT, "[ESPACO] para atirar");
            	al_draw_textf(opensans, al_map_rgb(255, 255, 255),70 ,460 ,ALLEGRO_ALIGN_LEFT, "[ESC] para sair do jogo");
            	al_draw_textf(opensans, al_map_rgb(255, 255, 255),70 ,490 ,ALLEGRO_ALIGN_LEFT, "[P] para pausar/continuar");
            	al_draw_textf(opensans, al_map_rgb(255, 255, 255),70 ,520 ,ALLEGRO_ALIGN_LEFT, "[H] ou [F1] para abrir/fechar a ajuda");
                al_draw_textf(opensans, al_map_rgb(255, 255, 255),70 ,550 ,ALLEGRO_ALIGN_LEFT, "[I] para ver os creditos");
            	al_draw_textf(font, al_map_rgb(255, 255, 255),70 ,580 ,ALLEGRO_ALIGN_LEFT, "(jogue 3 vezes sem fechar o programa e aperte [I] ver o easter egg)");
				al_draw_textf(font, al_map_rgb(255, 255, 255),70 ,600 ,ALLEGRO_ALIGN_LEFT, "(no menu principal inicie o jogo com F11 para o cheatmode)");          
            }	


            al_flip_display();
            redraw = false;
        }
    }

    al_stop_samples();
    al_destroy_font(font);
    al_destroy_font(captureit1);
    al_destroy_font(captureit2);
    al_destroy_font(opensans);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_sample(somtiro);
    al_destroy_sample(sommorteinimigo);
    al_destroy_sample(somnuke);
    al_destroy_sample(somfundo);

    al_destroy_bitmap(spritejogador1);
    al_destroy_bitmap(spritejogador2);
    al_destroy_bitmap(spriteinimigo1);
    al_destroy_bitmap(spriteparede);
    al_destroy_bitmap(spritebarreira);
    al_destroy_bitmap(spriteagua);
    al_destroy_bitmap(spritemato1);
    al_destroy_bitmap(spritemato2);
    al_destroy_bitmap(spriteinsignia);
    al_destroy_bitmap(spritenuke1);
    al_destroy_bitmap(spritenuke2);

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
    destroi_lista(&explosoes);

    return pontuacao;
}






























void fimdejogo1(ALLEGRO_DISPLAY* disp,int pontos,int *continuar){

    ALLEGRO_FONT* font = al_create_builtin_font();
    must_init(font,"fonte");

    FILE * scores = fopen("highscores.txt","r");
    must_init(scores,"arquivo de scores");

    int i;
    tscore *high = (tscore*) malloc(11*sizeof(tscore)); 

    must_init(high,"arro ao alocar memoria");
    for(i = 0 ; i < 10;i++){
        fscanf(scores,"%i",&high[i].score);
        fgets(high[i].nome,20,scores);
    }

   

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool done = false;
    bool redraw = true;
    bool jogar = false;
    ALLEGRO_EVENT event;
    
    al_start_timer(timer);
    char str[19];

    strcpy(str,"");

    while(1){
        al_wait_for_event(queue, &event);
        al_clear_to_color(al_map_rgb(30, 30, 30));

        switch(event.type){
            case ALLEGRO_EVENT_TIMER:
                redraw = true; 
                break;

            case ALLEGRO_EVENT_KEY_CHAR:
                if(event.keyboard.keycode == ALLEGRO_KEY_ENTER){
                    *continuar = *continuar + 1;
                    jogar = true;
                }
                else if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                    jogar = true;    
                    *continuar = 0;
                }
                else if (strlen(str) <= 19){
                    //  INICIO DO CODIGO RETIRADO DE https://gist.github.com/rafaeltoledo/6e157f233e94168d1af0fb2ee988cc19#file-tutorial14-c
                    //  o codigo verifica se o teclado escreveu uma caractere utilizavel
                        char temp[] = {event.keyboard.unichar, '\0'};
                    if (event.keyboard.unichar == ' '){
                        strcat(str, temp);
                    }
                    else if (event.keyboard.unichar >= '0' && event.keyboard.unichar <= '9'){
                        strcat(str, temp);
                    }
                    else if (event.keyboard.unichar >= 'A' && event.keyboard.unichar <= 'Z'){
                        strcat(str, temp);
                    }
                    else if (event.keyboard.unichar >= 'a' && event.keyboard.unichar <= 'z'){
                        strcat(str, temp);
                    }
                }
                //FIM DO CODIGO RETIRADO 
                redraw = true;   
                break;


            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }
        
        if(done)
            exit(0);

        if(jogar)
            break;

        if(redraw && al_is_event_queue_empty(queue)){
            al_draw_textf(font, al_map_rgb(255, 255, 255),100, 70 , 0, "FIM DE JOGO");
            al_draw_text(font, al_map_rgb(255, 255, 255),250, 320 , 0, str);
            for (i = 1 ; i < 10 ; i++){
                al_draw_textf(font, al_map_rgb(255, 255, 255),400, 100+32*i , 0, "%i",high[i].score);
                al_draw_textf(font, al_map_rgb(255, 255, 255),450, 100+32*i , 0, "%s",high[i].nome);
            }

            
            al_flip_display();
            redraw = false;
            //MENU BONITINHO
        }
    }
    al_destroy_font(font);






	return;
}
