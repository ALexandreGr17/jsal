CC=gcc
CFLAGS=-Wall -g
SRC=./main.c ./token.c stack.c
all:
	$(CC) $(SRC) $(CFLAGS)
