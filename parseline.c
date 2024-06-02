#include "shell.h"

char **parse_line(char *line){
    size_t buffer_size = TOKEN_BUFFER_SIZE;
    size_t position = 0;
    char **tokens = malloc(buffer_size * sizeof(char *));
    char *token;

    if (!tokens) {
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, TOKEN_DELIMITERS);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        // Reallocate if exceeded buffer size
        if (position + 1 >= buffer_size) {
            buffer_size += TOKEN_BUFFER_SIZE;
            char **new_tokens = realloc(tokens, buffer_size * sizeof(char *));
            if (!new_tokens) {
                fprintf(stderr, "Allocation error\n");
                free(tokens);
                exit(EXIT_FAILURE);
            }
            tokens = new_tokens;

        }

        token = strtok(NULL, TOKEN_DELIMITERS);
    }
    tokens[position] = NULL;
    return tokens;
}