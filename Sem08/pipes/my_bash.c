#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "parser.h"

#define MAX_CMD_LEN 1024

int execute_command(ParsedInput *parsed) {
    pid_t pid = fork();
    if (pid == 0) {
        Command cmd = parsed->commands[0];
        if (cmd.output) {
            int fd = open(cmd.output, O_WRONLY | O_CREAT |
                          (cmd.append ? O_APPEND : O_TRUNC), 0644);
            if (fd < 0) {
                perror("open");
                _exit(1);
            }
            if (dup2(fd, STDOUT_FILENO) < 0) {
                perror("dup2");
                _exit(1);
            }
            if (fd != STDOUT_FILENO) {
                close(fd);
            }
        }
        execvp(cmd.args[0], cmd.args);
        perror("exec");
        _exit(1);
    }

    int status;
    waitpid(pid, &status, 0);

    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    }
    return 1;
}

void print_prompt() {
    printf("\033[1;33mEnter command\033[0m$ ");
}

int main() {
    char cmd[MAX_CMD_LEN];

    while (1) {
        print_prompt();

        if (!fgets(cmd, sizeof(cmd), stdin)) {
            break;
        }
        cmd[strcspn(cmd, "\n")] = '\0';

        ParsedInput parsed;
        parse_input(cmd, &parsed);
        if (!parsed.commands[0].args[0]) {
            continue;
        }
        print_parsed(&parsed);

        if (execute_command(&parsed)) {
           printf("!! Non zero exit status !!\n");
        }
    }
    return 0;
}
