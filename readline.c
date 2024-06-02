#include "shell.h"

char *read_line(void){
    int buffer_size = READ_LINE_BUFFER_SIZE;
    char *buffer = (char *) malloc(buffer_size);
    int character;
    int counter = 0;
    int status = 1;

    if (!buffer) {
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
    }

    do {
        character = getchar();
        if ( character == EOF || character == '\n' ){
            status = 0;
        } else if (counter + 1 >= buffer_size){
            // Reallocate because of exceeded buffer size
            buffer_size *= 2;
            char *new_buffer = realloc(buffer, buffer_size);
            if (!new_buffer) {
                fprintf(stderr, "Allocation error\n");
                free(buffer);
                exit(EXIT_FAILURE);
            }
            buffer = new_buffer;

        } else {
            buffer[counter] = (char)character;
            counter++;
        }


    } while (status);

    buffer[counter] = '\0';
    return buffer;
}