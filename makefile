main : main.o fonctions.o save.o affichage.o
	gcc -o main main.o fonctions.o save.o affichage.o -g

main.o : main.c
	gcc -c main.c -g

fonctions.o : fonctions.c
	gcc -c fonctions.c -g

save.o : save.c
	gcc -c save.c -g

affichage.o : affichage.c
	gcc -c affichage.c -g

clean :
	rm -f *.o