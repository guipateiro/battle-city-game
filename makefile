# GRR20197152 Guilherme Costa Pateiro
# Universidade Federal do Parana , programacao2 - ERE2 A
# ultima edicao; 17/11/2020 17:11
CFLAGS = -std=gnu99 -Wall 

all:	liblista.o
	gcc jogo.c liblista.o $(CFLAGS) `pkg-config allegro_acodec-5 allegro-5 allegro_font-5 allegro_image-5  allegro_primitives-5 allegro_audio-5 --libs` -o teste

debug:	liblista.o
	gcc -g jogo.c liblista.o $(CFLAGS) `pkg-config allegro_acodec-5 allegro-5 allegro_font-5 allegro_image-5  allegro_primitives-5 allegro_audio-5 --libs` -o teste

run: all
	./teste 

liblista.o:	liblista.c    liblista.h  
	gcc -c  liblista.c $(CFLAGS) `pkg-config allegro-5  allegro_image-5 --libs`

clean:
	rm -f *.o	

purge:	clean
	rm -f teste