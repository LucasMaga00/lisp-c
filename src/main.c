#include <stdio.h>
#include <stdlib.h>

#include "mpc.h"
#include <histedit.h>

// argc = argument count
// argv = argument vector
// take a command like this -> ./program hello world
// argc = 3
// argv[0] = ./program ; argv[1] = hello ; argv[2] = world ; argv[3] = NULL
// char *argv[] = char **argv (because an array parameter decays to a pointer)

int main(int argc, char *argv[]) {

  EditLine *el = el_init("lispy", stdin, stdout, stderr);
  History *hist = history_init();
  HistEvent ev;

  history(hist, &ev, H_SETSIZE, 100);
  el_set(el, EL_HIST, history, hist);

  mpc_parser_t *Number = mpc_new("number");
  mpc_parser_t *Operator = mpc_new("operator");
  mpc_parser_t *Expr = mpc_new("expr");
  mpc_parser_t *Lispy = mpc_new("lispy");

  mpca_lang(MPCA_LANG_DEFAULT,
            "                                                     \
    number   : /-?[0-9]+/ ;                             \
    operator : '+' | '-' | '*' | '/' ;                  \
    expr     : <number> | '(' <operator> <expr>+ ')' ;  \
    lispy    : /^/ <operator> <expr>+ /$/ ;             \
  ",
            Number, Operator, Expr, Lispy);

  puts("Lispy Version 0.0.0.0.1");
  puts("Press Ctrl+c to Exit\n");

  el_set(el, EL_HIST, history, hist);

  while (1) {
    int count;

    const char *input = el_gets(el, &count);

    if (input == NULL) {
      break;
    }

    history(hist, &ev, H_ENTER, input);
    printf("No you're a %s", input);
  }

  history_end(hist);
  el_end(el);

  mpc_cleanup(4, Number, Operator, Expr, Lispy);
  return 0;
}
