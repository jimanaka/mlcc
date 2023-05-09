#include <stdio.h>
#include <string.h>
#include "lexer.h"

#define INITIAL_TOKEN_SIZE 16

static const char *whitespace = " \t\r\n\v";
static const char *symbols = "-+=()*&^%!~|{}[];'\",.<>/?`";

static enum state {
    IN_WORD,
    OUT_WORD,
};

static void add_token(struct token **tokens, size_t *tokens_count, struct token *current_token)
{
    if (current_token->size <= 0) {
        return;
    }

    *(tokens + *tokens_count) = (struct token*)malloc(sizeof(struct token*));
    memcpy(*(tokens + *tokens_count), current_token, sizeof(struct token));
    (*tokens_count)++;
    token_free(current_token);
}

static void reallocate_token_value(struct token *current_token)
{
    current_token->value = realloc(current_token->value, current_token->max_size * 2);
    if (current_token->value == NULL) {
        fprintf(stderr, "failed to reallocate token memory\n");
        exit(EXIT_FAILURE);
    }
    current_token->max_size = current_token->max_size * 2;
}


static void cat_token_value(struct token *current_token, char *current_char)
{
    if (current_token->size + 1 > current_token->max_size) {
        reallocate_token_value(current_token);
    }
    char buffer[current_token->max_size];
    memset(buffer, 0, sizeof(buffer));

    snprintf(buffer, current_token->max_size, "%s%s", current_token->value, current_char);
    current_token->size++;
    strcpy(current_token->value, buffer);
}

static struct token* token_create() {
    struct token *current_token = (struct token*) malloc(sizeof(struct token));
    current_token->value = (char*) malloc(INITIAL_TOKEN_SIZE * sizeof(char));
    current_token->size = 0;
    current_token->max_size = INITIAL_TOKEN_SIZE;

    return current_token;
}

void token_free(struct token *current_token) {
    free(current_token);
}

/// @brief Splits text file into lexical tokens
/// @param file file to lex
/// @param tokens buffer to store tokens
/// @return token_count, number of generated tokens 
int lex_file(FILE *file, struct token **tokens)
{
    char current_char[2] = {'\0', '\0'};
    struct token *current_token = token_create();
    size_t tokens_count = 0;

    enum state state = OUT_WORD;

    while ((current_char[0] = fgetc(file)) != EOF)
    {
        if (strchr(whitespace, current_char[0]) != NULL) {
            if (state == OUT_WORD) continue;

            // Add current_token to tokens array
            add_token(tokens, &tokens_count, current_token);
            // set state to OUT_WORD
            state = OUT_WORD;
            continue;
        }

        // cat char to current token + increase token length
        if (state == OUT_WORD) {
            current_token = token_create();
            state = IN_WORD;
        }

        if(strchr(symbols, current_char[0]) != NULL) {
            add_token(tokens, &tokens_count, current_token);
            current_token = token_create();
            cat_token_value(current_token, current_char);
            add_token(tokens, &tokens_count, current_token);
            state = OUT_WORD;
            continue;
        }

        cat_token_value(current_token, current_char);
    }

    return tokens_count;
}