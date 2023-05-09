#include <stdio.h>
#include <string.h>
#include "lexer.h"

static char *whitespace = " \t\r\n\v";

static enum state {
    IN_WORD,
    OUT_WORD,
};

static void add_token(char **tokens, size_t num_tokens, char *current_token, size_t current_token_length)
{
    // (tokens + num_tokens) = 0;
}

/// @brief Splits text file into lexical tokens
/// @param file file to lex
/// @param tokens buffer to store tokens
/// @return 0 if success, -1 if failure
int lex_file(FILE *file, char **tokens)
{
    char current_char;
    char *current_token = "";
    enum state state = OUT_WORD;

    while ((current_char = fgetc(file)) != EOF)
    {
        if (strchr(whitespace, current_char) == NULL) {
            if (state == OUT_WORD) continue;
        }

        switch (current_char)
        {
            default:
                return;
        }

    }

    return 0;
}