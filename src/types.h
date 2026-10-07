#ifndef TYPES_H
#define TYPES_H

typedef struct lval lval;
typedef struct lenv lenv;

typedef lval *(*lbuiltin)(lenv *, lval *);

#endif
