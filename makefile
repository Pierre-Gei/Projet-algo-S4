main: main.o init.o affichage.o menus.o fonctions.o niveau1.o niveau2.o save.o 
	gcc -o main main.o init.o  affichage.o menus.o fonctions.o niveau1.o niveau2.o save.o -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer 

main.o: main.c
	gcc -c main.c -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer 	

init.o: init.c
	gcc -c init.c -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer 

affichage.o: affichage.c
	gcc -c affichage.c -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer 
menus.o: menus.c
	gcc -c menus.c -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer 

fonctions.o: fonctions.c
	gcc -c fonctions.c -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer 

niveau1.o: niveau1.c
	gcc -c niveau1.c -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer 

niveau2.o: niveau2.c
	gcc -c niveau2.c -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer 

save.o: save.c
	gcc -c save.c -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer 

clean:
	rm -f main main.o