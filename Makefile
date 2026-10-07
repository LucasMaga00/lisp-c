CC = cc
CFLAGS = -std=c99 -Wall -Wextra -Wpedantic -g

program: src/main.c src/eval.c src/env.c src/builtin.c src/mpc.c \
         src/types.h src/eval.h src/env.h src/builtin.h src/mpc.h Makefile
	$(CC) $(CFLAGS) src/main.c src/eval.c src/env.c src/builtin.c src/mpc.c -o program -ledit -lm

.PHONY: run
run: program
	./program
