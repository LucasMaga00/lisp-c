# Lisp in C

A small Lisp interpreter built in C as a learning project. It uses the bundled
MPC parser and supports numbers, strings, lists, variables, functions, conditionals,
comments, and loading source files.

## Build and run

Requires a C99 compiler, Make, and the libedit headers and library (`histedit.h`).

```sh
make
./program
```

You can also start the interactive interpreter with `make run`. Press Ctrl+C to exit.

## Examples

Enter these expressions one line at a time:

```lisp
(+ 1 2)
(def {answer} 42)
answer
(head {1 2 3})
(fun {square x} {* x x})
(square 5)
(print "Hello, world!")
; Comments start with a semicolon
```

## Load a file

Put parenthesized expressions in a file such as `example.lspy`, then run:

```sh
./program example.lspy
```

The file is evaluated before the interactive session starts. Use `print` to display
results from a file. You can also load a file during a session:

```lisp
(load "example.lspy")
```
