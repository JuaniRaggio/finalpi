CC = gcc
CFLAGS = -I./validations -I./backend I./frontend -g -Wall -std=c99 -fsanitize=address -pedantic

SRC = ./main.c ./validationsIDADT.c ./modulo2.c

program: $(SRC)
	$(CC) $(CFLAGS) $(SRC)
