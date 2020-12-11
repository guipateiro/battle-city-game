# GRR20197152 Guilherme Costa Pateiro
# Universidade Federal do Parana , programacao2 - ERE2 A
# ultima edicao; 09/12/2020 19:40
CFLAGS = -std=gnu99 -Wall
LDLIBS = `pkg-config allegro_ttf-5 allegro_acodec-5 allegro-5 allegro_font-5 allegro_image-5  allegro_primitives-5 allegro_audio-5 --libs`
OBJECTS = liblista.o jogo.o macrojogo.o  battlecity.o

all:	$(OBJECTS)
	gcc -o battlecity $(OBJECTS) $(CFLAGS) $(LDLIBS) 

run: all
	./battlecity 

battlecity.o:	battlecity.c
	gcc  -c battlecity.c $(CFLAGS)

macrojogo.o: macrojogo.c 	macrojogo.h 
	gcc  -c macrojogo.c $(CFLAGS)  

jogo.o:	jogo.c 	jogo.h	
	gcc -c jogo.c $(CFLAGS) 

liblista.o:	liblista.c    liblista.h  
	gcc -c  liblista.c $(CFLAGS) 

clean:
	rm -f *.o	

purge:	clean
	rm -f battlecity