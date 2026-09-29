#include <stdio.h>

// argc = argument count
// argv = argument vector
// take a command like this -> ./program hello world
// argc = 3
// argv[0] = ./program ; argv[1] = hello ; argv[2] = world ; argv[3] = NULL
// char *argv[] = char **argv (because an array parameter decays to a pointer)
static char input[2048];

int main(int argc, char *argv[]) {

  puts("Lispy Version 0.0.0.0.1");
  puts("Press Ctrl+c to Exit\n");

  while (1) {
    fputs("lispy>", stdout);
    fgets(input, 2048, stdin);
    printf("No you're a %s", input);
  }

  return 0;
}
