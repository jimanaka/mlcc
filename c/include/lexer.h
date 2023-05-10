#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>

enum TOKEN_TYPES {
    IDENTIFIER,
    KEYWORD,
    INTEGER,
    CHARACTER,
    REAL_NUMBER,
    STRING,
    SEPARATOR,
    WHITE_SPACE,
    UNARY_OPERATOR,
    ARITHMATIC_OPERATOR,
    RELATIONAL_OPERATOR,
    LOGICAL_OPERATOR,
    BITWISE_OPERATOR,
    ASSIGNMENT_OPERATOR,
    // TERNARY?
};

/// @brief 
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