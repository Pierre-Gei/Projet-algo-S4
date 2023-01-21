# Path: src/makefile
CFLAGS := $(shell pkg-config --cflags sdl2)
LDFLAGS := $(shell pkg-config --libs sdl2)

main: main.o fonctions.o affichage.o save.o
	$(CC) $(CFLAGS) -o main main.o fonctions.o affichage.o save.o -g $(LDFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -g

fonctions.o: fonctions.c fonctions.h
	$(CC) $(CFLAGS) -c fonctions.c -g

affichage.o: affichage.c affichage.h
	$(CC) $(CFLAGS) -c affichage.c -g

save.o: save.c save.h
	$(CC) $(CFLAGS) -c save.c -g

clean:
	rm -f main main.o