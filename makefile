main: main.o affichage.o fonctions.o save.o
	gcc -o main main.o affichage.o fonctions.o save.o -lSDL2 -lSDL2_image

main.o: main.c
	gcc -c main.c -lSDL2 -lSDL2_image  

affichage.o: affichage.c
	gcc -c affichage.c -lSDL2 -lSDL2_image

fonctions.o: fonctions.c
	gcc -c fonctions.c -lSDL2 -lSDL2_image

save.o: save.c
	gcc -c save.c -lSDL2 -lSDL2_image
clean:
	rm -f main main.o