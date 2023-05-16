#include <stdio.h>
#include <string.h>
#include "lexer.h"

#define INITIAL_TOKEN_SIZE 16

static const char *whitespace = " \t\r\n\v";
static const char *separators = "(){}[];,.";
static const char *operators = "+-*/\%<>=&|!~^";

static enum STATE {
    IN_WORD,
    IN_STRING,
    IN_CHAR,
    IN_OP,
    OUT_WORD,
} state = OUT_WORD;

static struct token* token_create() {
    struct token *current_token = (struct token*) malloc(sizeof(struct token));
    current_token->value = (char*) calloc(INITIAL_TOKEN_SIZE, sizeof(char));
    current_token->size = 0;
    current_token->max_size = INITIAL_TOKEN_SIZE;

    return current_token;
}

void token_free(struct token *current_token) {
    free(current_token->value);
    free(current_token);
}
static void add_token(struct token **tokens, size_t *tokens_count, struct token *current_token)
{
    if (current_token->size <= 0) {
        return;
    }
    printf("adding token: %s\n", current_token->value);

    *(tokens + *tokens_count) = (struct token*)malloc(sizeof(struct token*));
    memcpy(*(tokens + *tokens_count), current_token, sizeof(struct token));
    (*(tokens + *tokens_count))->value = (char *)calloc(current_token->max_size, sizeof(char));
    strcpy((*(tokens + *tokens_count))->value, current_token->value);
    (*tokens_count)++;
    token_free(current_token);
    current_token = token_create();
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


static int eat_char(const char read_char, struct token *current_token, struct token **tokens, size_t *tokens_count)
{
    char current_char[2] = {read_char, '\0'};
    // if operator check if last_char was operator
    // if yes -> cat two together, store in token, add token to tokens
    // if no -> store operator in last_char, return
    // if last_char is an operator and you have anything else, add current_token to tokens, make new token to store new value in
    printf("Eating char: %c\n", read_char);
    if (strchr(operators, current_char[0]) != NULL) {
        if (state == IN_OP) {
            cat_token_value(current_token, current_char);
            add_token(tokens, tokens_count, current_token);
            state = OUT_WORD;
            return 0;
        }

        add_token(tokens, tokens_count, current_token);
        cat_token_value(current_token, current_char);
        state = IN_OP;
        return 0;
    }

    if (state == IN_OP) {
        add_token(tokens, tokens_count, current_token);
        state = OUT_WORD;
    }


    // if whitespace -> check if inside word or out of word
    // if out of word -> do nothing
    // if in word -> add current token to tokens
    if (strchr(whitespace, current_char[0]) != NULL) {
        if (state == OUT_WORD) return 0;

        add_token(tokens, tokens_count, current_token);
        state = OUT_WORD;
        return 0;
    }

    // if separator -> add current token to tokens
        // create new token, cat separator, add current token to tokens
    if (strchr(separators, current_char[0]) != NULL) {
        if (state != OUT_WORD) {
            add_token(tokens, tokens_count, current_token);
        }
        cat_token_value(current_token, current_char);
        add_token(tokens, tokens_count, current_token);
        state = OUT_WORD;
        return 0;
    }
    

    // if string_separator all chars are stored in same token until the same string sep is found
    // def a better way to do this, probably switch statement
    if (current_char[0] == '\"') {
        if (state != IN_STRING) {
            add_token(tokens, tokens_count, current_token);
            cat_token_value(current_token, current_char);
            state = IN_STRING;
            return 0;
        } else {
            cat_token_value(current_token, current_char);
            add_token(tokens, tokens_count, current_token);
            state = OUT_WORD;
            return 0;
        }
    }

    //if char separator, all chars are stored in same token until the same char sep is found.  if first char is not '\', then the char token cannot have size > 1
    // again, probably should use a switch
    if (current_char[0] == '\'') {
        if (state != IN_CHAR) {
            add_token(tokens, tokens_count, current_token);
            cat_token_value(current_token, current_char);
            state = IN_CHAR;
            return 0;
        } else {
            cat_token_value(current_token, current_char);
            add_token(tokens, tokens_count, current_token);
            state = OUT_WORD;
            return 0;
        }
    }

    if (state == OUT_WORD) {
        state = IN_WORD;
    }

    cat_token_value(current_token, current_char);

    return 0;
}

/// @brief Splits text file into lexical tokens
/// @param file file to lex
/// @param tokens buffer to store tokens
/// @return token_count, number of generated tokens 
int lex_file(FILE *file, struct token **tokens)
{
    char current_char = '\0';
    size_t tokens_count = 0;
    struct token *current_token = token_create();

    while ((current_char = fgetc(file)) != EOF)
    {
        eat_char(current_char, current_token, tokens, &tokens_count);
    }
    printf("token count: %d\n", tokens_count);

    return tokens_count;
}