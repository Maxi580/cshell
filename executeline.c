#include "shell.h"

int built_in_cd(char **args){
    if (args[1] == NULL) {
        fprintf(stderr, "cd: expected argument\n");
        return 1;
    } else {
        if (chdir(args[1]) != 0) {
            perror("cd failed");
            return 0;
        }
    }
    return 1;
}

int built_in_exit(char **args){
    return 0;
}

char *builtins[] = {"cd", "exit"};

int (*builtin_func[]) (char **) = {
        &built_in_cd,
        &built_in_exit
};

int execute_line_in_child_process(char **parsed_line){
    pid_t pid;


    pid = fork();
    int status;

    if (pid == 0) {
        //Child Process: execute command
        execvp(parsed_line[0], parsed_line);

        // If execvp returns, it must have failed
        perror("Command execution failed");
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("Fork failed, while executing the command");
        return 0;
    } else {
        //Parent Process: wait the child process is finished
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

int execute_line(char **parsed_line){
    //Executes built in commands in the parent process, as here the process doesn't get killed after execution
    int i;
    for (i=0; i < sizeof(builtins) / sizeof(char *); i++){
        if (strcmp(parsed_line[0], builtins[i]) == 0){
            return builtin_func[i](parsed_line);

        }
    }
    return execute_line_in_child_process(parsed_line);
}