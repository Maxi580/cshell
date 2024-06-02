#include "shell.h"

void shell_loop(void){
    char *line;
    char **parsed_line;
    int status;

    do{
        printf(">");

        line = read_line();
        parsed_line = parse_line(line);

        if (parsed_line[0] == NULL) {
            free(line);
            free(parsed_line);
            continue;
        }

        status = execute_line(parsed_line);

        free(line);
        free(parsed_line);
    } while (status);
}

int main(int argc, char **argv){

    //Execute the main loop
    shell_loop();

    return EXIT_SUCCESS;
}

