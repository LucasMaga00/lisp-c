#ifndef EVAL_H
#define EVAL_H

#include "mpc.h"
#include "types.h"

enum { LVAL_NUM, LVAL_ERR, LVAL_SYM, LVAL_SEXPR, LVAL_QEXPR, LVAL_FUN };

struct lval {
  int type;

  // Basic
  long num;
  char *err;
  char *sym;

  // Function
  lbuiltin builtin;
  lenv *env;
  lval *formals;
  lval *body;

  // Expressions
  int count;
  struct lval **cell;
};

lval *lval_eval(lenv *e, lval *v);
lval *lval_join(lval *x, lval *y);
lval *lval_num(long x);
lval *lval_err(char *fmt, ...);
lval *lval_sym(char *s);
lval *lval_sexpr(void);
lval *lval_fun(lbuiltin funk);
lval *lval_lambda(lval *formals, lval *body);
lval *lval_read(mpc_ast_t *t);
lval *lval_add(lval *v, lval *x);
lval *lval_pop(lval *v, int i);
lval *lval_take(lval *v, int i);
lval *lval_copy(lval *v);

int lval_eq(lval *x, lval *y);

void lval_println(lval *v);
void lval_del(lval *v);

char *ltype_name(int t);

#endif
