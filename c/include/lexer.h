#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>

/* Splits file into tokens */
int lex_file(FILE *file, char **tokens);

#endif 