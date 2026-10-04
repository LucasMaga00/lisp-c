CC = cc
CFLAGS = -std=c99 -Wall -Wextra -Wpedantic -g

program: src/main.c src/mpc.c src/mpc.h src/eval.c src/eval.h Makefile
	$(CC) $(CFLAGS) src/main.c src/eval.c src/mpc.c -o program -ledit -lm

.PHONY: run
run: program
	./program
