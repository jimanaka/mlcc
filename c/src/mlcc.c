#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mlcc.h"
#include "lexer.h"

int main(int argc, char *argv[])
{
    if (argc != 2 ) 
    {
        fprintf(stderr, "%s: Usage: ./mlcc <filename.c>\n", PROGRAM_NAME);
        return EXIT_FAILURE;
    }

    int error = 0;

    char filename[128];
    memset(filename, 0, sizeof(filename));
    strcpy(filename, argv[1]);
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "%s: Could not open file <%s>\n", PROGRAM_NAME, filename);
        exit(EXIT_FAILURE);
    }

    // Pass file through lexer
    int token_count = 0;
    struct token **tokens = (char **)malloc(1024 * sizeof(struct token*));
    token_count = lex_file(file, tokens);

    for (int i = 0; i < token_count; i++)
    {
        printf("token[%d]: %s\n", i, (*(tokens+i))->value);
    }

    for(int i = 0; i < token_count; i++)
    {
        token_free(*(tokens + i));
    }

    free(tokens);

    return 0;
}