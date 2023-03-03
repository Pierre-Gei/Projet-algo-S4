main: main.o init.o affichage.o fonctions.o niveau1.o save.o 
	gcc -o main main.o init.o  affichage.o fonctions.o niveau1.o save.o -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm

main.o: main.c
	gcc -c main.c -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm	

init.o: init.c
	gcc -c init.c -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm

affichage.o: affichage.c
	gcc -c affichage.c -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm

fonctions.o: fonctions.c
	gcc -c fonctions.c -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm

niveau1.o: niveau1.c
	gcc -c niveau1.c -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm

save.o: save.c
	gcc -c save.c -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm

clean:
	rm -f main main.o