CC=gcc
CFLAGS=-Wall -g
LIBS=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11

reel-fishin: main.o
	$(CC) main.c screenLayouts.c $(CFLAGS) $(LIBS) -o reel-fishin.out
