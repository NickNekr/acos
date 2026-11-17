#include <stdio.h>
#include <unistd.h>

int main(void) {
    int fds[2];
    if (pipe(fds) < 0) {
        perror("pipe");
        return 1;
    }

    if (write(fds[1], "hello", 5) < 0) {
        perror("write");
        return 1;
    }
    // А если не закрыть?
    close(fds[1]);

    char buf[16];
    ssize_t n;
    while ((n = read(fds[0], buf, sizeof buf)) > 0) {
        printf("%.*s\n", (int)n, buf);
    }
    if (n < 0) {
        perror("read");
        return 1;
    }
    printf("read: %zd (EOF)\n", n);
    close(fds[0]);
    return 0;
}
