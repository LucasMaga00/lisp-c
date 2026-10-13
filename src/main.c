#include <stdio.h>
#include <stdlib.h>

#include "builtin.h"
#include "env.h"
#include "eval.h"
#include "mpc.h"
#include <histedit.h>

// argc = argument count
// argv = argument vector
// take a command like this -> ./program hello world
// argc = 3
// argv[0] = ./program ; argv[1] = hello ; argv[2] = world ; argv[3] = NULL
// char *argv[] = char **argv (because an array parameter decays to a pointer)

mpc_parser_t *Number;
mpc_parser_t *Symbol;
mpc_parser_t *Sexpr;
mpc_parser_t *Qexpr;
mpc_parser_t *Expr;
mpc_parser_t *Lispy;
mpc_parser_t *String;
mpc_parser_t *Comment;

int main(int argc, char *argv[]) {

  EditLine *el = el_init("lispy", stdin, stdout, stderr);
  History *hist = history_init();
  HistEvent ev;

  history(hist, &ev, H_SETSIZE, 100);
  el_set(el, EL_HIST, history, hist);

  Number = mpc_new("number");
  Symbol = mpc_new("symbol");
  Sexpr = mpc_new("sexpr");
  Qexpr = mpc_new("qexpr");
  Expr = mpc_new("expr");
  Lispy = mpc_new("lispy");
  String = mpc_new("string");
  Comment = mpc_new("comment");

  mpca_lang(MPCA_LANG_DEFAULT, "                         \
    number   : /-?[0-9]+/                          ;     \
    symbol   : /[a-zA-Z0-9_+\\-*\\/\\\\=<>!&|]+/         \
             | \"join\" | \"eval\" | \"list\"            \
             | \"head\" | \"tail\"                 ;     \
    sexpr    : '(' <expr>* ')'                     ;     \
    qexpr    : '{' <expr>* '}'                     ;     \
    expr     : <number> | <symbol> | <sexpr>             \
             | <qexpr> | <string> | <comment>      ;     \
    lispy    : /^/ <expr>* /$/                     ;     \
    string   : /\"(\\\\.|[^\"])*\"/                ;     \
    comment  : /;[^\\r\\n]*/                       ;     \
  ",
            Number, Symbol, Sexpr, Qexpr, Expr, Lispy, String, Comment);

  puts("Lispy Version 0.0.0.0.6");
  puts("Press Ctrl+c to Exit\n");

  el_set(el, EL_HIST, history, hist);

  lenv *e = lenv_new();
  lenv_add_builtins(e);

  if (argc >= 2) {
    for (int i = 1; i < argc; i++) {
      lval *args = lval_add(lval_sexpr(), lval_str(argv[i]));
      lval *x = builtin_load(e, args);
      if (x->type == LVAL_ERR) {
        lval_println(x);
      }
      lval_del(x);
    }
  }

  while (1) {
    int count;

    const char *input = el_gets(el, &count);

    if (input == NULL) {
      break;
    }

    history(hist, &ev, H_ENTER, input);
    mpc_result_t r;
    if (mpc_parse("<stdin>", input, Lispy, &r)) {
      lval *x = lval_eval(e, lval_read(r.output));
      lval_println(x);
      lval_del(x);
      mpc_ast_delete(r.output);
    } else {
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }
  }

  lenv_del(e);
  history_end(hist);
  el_end(el);

  mpc_cleanup(8, Number, Symbol, Sexpr, Qexpr, Expr, Lispy, String, Comment);
  return 0;
}
