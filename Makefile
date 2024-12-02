CC = gcc
CFLAGS = -I./lib -I./validations -I./backend I./frontend -g -Wall -std=c99 -fsanitize=address -pedantic

SRC = ./main.c ./validationsIDADT.c ./modulo2.c

program: $(SRC)
	$(CC) $(CFLAGS) -o program $(SRC)
