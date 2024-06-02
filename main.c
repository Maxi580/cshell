#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <rpcndr.h>
#include <stdbool.h>

char *read_line(void){
    int buffer_size = 21;
    char *buffer = (char *) malloc(buffer_size);
    int character;
    int counter = 0;


    bool status = true;
    do {
       character = getchar();
       if ( character == EOF || character == '\n' )
       {
            status = false;
       }
       else if (counter + 1 >= buffer_size)
       {
            buffer_size *= 2;
           char *new_buffer = realloc(buffer, buffer_size);
           buffer = new_buffer;
       }
       else
       {
           buffer[counter] = (char)character;
           counter++;
       }


    } while (status);

    buffer[counter] = '\0';
    return buffer;
}


char *parse_line(char *line){

}

void execute_line(char *parsed_line){

}

void shell_loop(void){
    char *line;
    char *parsed_line;

    do{
        printf(">");

        line = read_line();
        parsed_line = parse_line(line);
        execute_line(parsed_line);

        free(line);
        free(parsed_line);

    } while (1);
}

int main(int argc, char **argv){

    //Execute the main loop
    shell_loop();


    return EXIT_SUCCESS;
}

