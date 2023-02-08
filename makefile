main: main.o affichage.o fonctions.o niveau1.o save.o init.o
	gcc -o main main.o affichage.o fonctions.o niveau1.o save.o init.o -lSDL2 -lSDL2_image -lm

main.o: main.c
	gcc -c main.c -lSDL2 -lSDL2_image -lm	

affichage.o: affichage.c
	gcc -c affichage.c -lSDL2 -lSDL2_image -lm

fonctions.o: fonctions.c
	gcc -c fonctions.c -lSDL2 -lSDL2_image -lm

niveau1.o: niveau1.c
	gcc -c niveau1.c -lSDL2 -lSDL2_image -lm

save.o: save.c
	gcc -c save.c -lSDL2 -lSDL2_image -lm

init.o: init.c
	gcc -c init.c -lSDL2 -lSDL2_image -lm
clean:
	rm -f main main.o