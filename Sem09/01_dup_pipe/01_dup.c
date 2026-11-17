#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

// ls -l > output.txt

int main(void) {
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    int fd2 = dup2(fd, STDOUT_FILENO);

    printf("Writing to fd: %d\n", fd);
    fflush(stdout);

    close(fd);
    close(fd2);


    return 0;
}
