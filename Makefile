CC = cc
CFLAGS = -std=c17 -Wall -Wextra -Wpedantic -g

program: src/main.c Makefile
	$(CC) $(CFLAGS) src/main.c -o program -ledit

.PHONY: run
run: program
	./program
