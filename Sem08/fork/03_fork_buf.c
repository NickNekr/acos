#include <stdio.h>
#include <unistd.h>

int main() {
    printf("hello world!\n");

    fork();
    exit(0);
}
