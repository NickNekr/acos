#include <stdio.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    int *x = mmap(NULL, sizeof *x, PROT_READ | PROT_WRITE,
                  MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (x == MAP_FAILED) {
        perror("mmap");
        return 1;
    }
    *x = 1;

    pid_t child = fork();
    if (child < 0) {
        perror("fork");
        return 1;
    }
    if (child == 0) {
        *x = 100;
        printf("Child: %d\n", *x);
        return 0;
    }

    if (waitpid(child, NULL, 0) < 0) {
        perror("waitpid");
        return 1;
    }
    printf("Parent: %d\n", *x);
    munmap(x, sizeof *x);
    return 0;
}
