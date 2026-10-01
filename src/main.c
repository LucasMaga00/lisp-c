#include <stdio.h>
#include <stdlib.h>

#include "mpc.h"
#include <histedit.h>

long eval(mpc_ast_t *t);
long eval_op(long x, char *op, long y);
int count_leaves(mpc_ast_t *t);

enum { LVAL_NUM, LVAL, ERR };
enum { LERR_DIV_ZERO, LERR_BAD_OP, LERR_BAD_NUM };

// argc = argument count
// argv = argument vector
// take a command like this -> ./program hello world
// argc = 3
// argv[0] = ./program ; argv[1] = hello ; argv[2] = world ; argv[3] = NULL
// char *argv[] = char **argv (because an array parameter decays to a pointer)

int main(void) {

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

  puts("Lispy Version 0.0.0.0.2");
  puts("Press Ctrl+c to Exit\n");

  el_set(el, EL_HIST, history, hist);

  while (1) {
    int count;

    const char *input = el_gets(el, &count);

    if (input == NULL) {
      break;
    }

    history(hist, &ev, H_ENTER, input);
    mpc_result_t r;
    if (mpc_parse("<stdin>", input, Lispy, &r)) {
      mpc_ast_print(r.output);
      long result = eval(r.output);
      printf("%li\n", result);
      int leaves = count_leaves(r.output);
      printf("%i\n", leaves);
      mpc_ast_delete(r.output);
    } else {
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }
  }

  history_end(hist);
  el_end(el);

  mpc_cleanup(4, Number, Operator, Expr, Lispy);
  return 0;
}

int count_leaves(mpc_ast_t *t) {
  if (t->children_num == 0) {
    return 1;
  }

  int total = 0;
  for (int i = 0; i < t->children_num; i++) {
    total += count_leaves(t->children[i]);
  }

  return total;
}

long eval(mpc_ast_t *t) {
  if (strstr(t->tag, "number")) {
    return atol(t->contents);
  }

  char *op = t->children[1]->contents;
  long x = eval(t->children[2]);

  int i = 3;
  while (strstr(t->children[i]->tag, "expr")) {
    x = eval_op(x, op, eval(t->children[i]));
    i++;
  }

  return x;
}

long eval_op(long x, char *op, long y) {
  if (strcmp(op, "+") == 0) {
    return x + y;
  }
  if (strcmp(op, "-") == 0) {
    return x - y;
  }
  if (strcmp(op, "*") == 0) {
    return x * y;
  }
  if (strcmp(op, "/") == 0) {
    return x / y;
  }
  return 0;
}
