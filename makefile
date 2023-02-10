main: main.o affichage.o fonctions.o niveau1.o save.o init.o
	gcc -o main main.o affichage.o fonctions.o niveau1.o save.o init.o -lSDL2 -lSDL2_image -lSDL2_ttf -lm

main.o: main.c
	gcc -c main.c -lSDL2 -lSDL2_image -lSDL2_ttf -lm	

affichage.o: affichage.c
	gcc -c affichage.c -lSDL2 -lSDL2_image -lSDL2_ttf -lm

fonctions.o: fonctions.c
	gcc -c fonctions.c -lSDL2 -lSDL2_image -lSDL2_ttf -lm

niveau1.o: niveau1.c
	gcc -c niveau1.c -lSDL2 -lSDL2_image -lSDL2_ttf-lm

save.o: save.c
	gcc -c save.c -lSDL2 -lSDL2_image -lSDL2_ttf -lm

init.o: init.c
	gcc -c init.c -lSDL2 -lSDL2_image -lSDL2_ttf -lm
clean:
	rm -f main main.o