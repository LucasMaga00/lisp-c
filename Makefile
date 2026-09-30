CC = cc
CFLAGS = -std=c99 -Wall -Wextra -Wpedantic -g

program: src/main.c src/mpc.c src/mpc.h Makefile
	$(CC) $(CFLAGS) src/main.c src/mpc.c -o program -ledit -lm

.PHONY: run
run: program
	./program
