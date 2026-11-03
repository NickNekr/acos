#include <stdio.h>
#include <unistd.h>

int main() {
    int x = 100;

    pid_t pid = fork();
    if (pid == 0) {
        sleep(5);
        printf("[Child] x = %d ppid: %d\n", x, getppid());
        _exit(0);
    }


    x = 1000;
    printf("[Parent] x = %d\n", x);
}
