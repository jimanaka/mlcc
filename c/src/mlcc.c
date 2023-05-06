#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mlcc.h"

#define HELLO 123

int main(int argc, char *argv[])
{

    printf("%s\n", TEST);
    if (argc != 2 ) 
    {
        fprintf(stderr, "%s: Usage: ./mlcc <filename.c>\n", PROGRAM_NAME);
        return EXIT_FAILURE;
    }

    char filename[128];
    memset(filename, 0, sizeof(filename));
    strcpy(filename, argv[1]);
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "%s: Could not open file <%s>\n", PROGRAM_NAME, filename);
        return EXIT_FAILURE;
    }

    return 0;
}