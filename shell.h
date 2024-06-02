// shell.h
#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define READ_LINE_BUFFER_SIZE 1024
#define TOKEN_BUFFER_SIZE 64
#define TOKEN_DELIMITERS " \t\r\n\a"

char *read_line(void);
char **parse_line(char *line);
int execute_statement(char **parsed_line);
int execute_line(char **parsed_line);
void shell_loop(void);

#endif // SHELL_H
