CC=gcc
VAL=valgrind
NAME=lista_se
CFLAGS=-g -Wall -Wconversion -Wtype-limits -pedantic -Werror -std=c99 -O0
VFLAGS=--leak-check=full --track-origins=yes --show-reachable=yes

build:
	$(CC) *.c -o $(NAME) $(CFLAGS)

valgrin: build
	$(VAL) $(VFLAGS) ./$(NAME)
