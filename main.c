#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define READ_LINE_BUFFER_SIZE 1024
#define TOKEN_BUFFER_SIZE 64
#define TOKEN_DELIMITERS " \t\r\n\a"

char *read_line(void){
    int buffer_size = READ_LINE_BUFFER_SIZE;
    char *buffer = (char *) malloc(buffer_size);
    int character;
    int counter = 0;

    if (!buffer) {
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
    }

    int status = 1;
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

int execute_line(char **parsed_line){
    pid_t pid;
    pid = fork();
    int status;

    if (pid == 0) {
        //Child Process: execute command
        execvp(parsed_line[0], parsed_line);

        // If execvp returns, it must have failed
        perror("Command execution failed");
    } else if (pid < 0) {
        perror("Fork failed, while executing the command");
    } else {
        //Parent Process: wait the child process is finished
        waitpid(pid, &status, 0);
    }
    return 1;
}

void shell_loop(void){
    char *line;
    char **parsed_line;
    int status;

    do{
        printf(">");

        line = read_line();
        parsed_line = parse_line(line);
        status = execute_line(parsed_line);

        free(line);
        free(parsed_line);

    } while (1);
}

int main(int argc, char **argv){

    //Execute the main loop
    shell_loop();

    return EXIT_SUCCESS;
}

