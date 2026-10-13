#include "mpc.h"

#ifndef TYPES_H
#define TYPES_H

typedef struct lval lval;
typedef struct lenv lenv;

typedef lval *(*lbuiltin)(lenv *, lval *);

extern mpc_parser_t *Number;
extern mpc_parser_t *Symbol;
extern mpc_parser_t *Sexpr;
extern mpc_parser_t *Qexpr;
extern mpc_parser_t *Expr;
extern mpc_parser_t *Lispy;
extern mpc_parser_t *String;
extern mpc_parser_t *Comment;

#endif
