#ifndef ENV_H
#define ENV_H

#include "types.h"

struct lenv {
  lenv *par;
  int count;
  char **syms;
  lval **vals;
};

lenv *lenv_new(void);
lenv *lenv_copy(lenv *v);
lval *lenv_get(lenv *e, lval *k);
void lenv_put(lenv *e, lval *k, lval *v);
void lenv_del(lenv *e);
void lenv_def(lenv *e, lval *k, lval *v);
void lenv_add_builtins(lenv *e);

#endif
