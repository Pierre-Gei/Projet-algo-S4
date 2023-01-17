# Path: src/makefile
CFLAGS := $(shell pkg-config --cflags sdl2)
LDFLAGS := $(shell pkg-config --libs sdl2)

main: main.o
	$(CC) $(CFLAGS) -o main main.o $(LDFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f main main.o