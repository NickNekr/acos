#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    int x = 1;

    pid_t child = fork();
    if (child < 0) {
        perror("fork");
        return 1;
    }
    if (child == 0) {
        x = 100;
        printf("Child: %d\n", x);
        return 0;
    }

    if (waitpid(child, NULL, 0) < 0) {
        perror("waitpid");
        return 1;
    }
    printf("Parent: %d\n", x);
    return 0;
}
