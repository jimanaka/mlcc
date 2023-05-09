#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>

struct token
{
    char* value;
    size_t size;
    size_t max_size;
};

/* Splits file into tokens */
int lex_file(FILE *file, struct token **tokens);

void token_free(struct token*);

#endif 