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
    char **tokens = (char **)malloc(1024 * sizeof(char*));
    error = lex_file(file, tokens);
    if (!error)
    {
        fprintf(stderr, "%s: Failed to lex file <%s>\n", PROGRAM_NAME, filename);
        exit(EXIT_FAILURE);
    }

    return 0;
}