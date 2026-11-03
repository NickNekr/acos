#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

unsigned good_checksum = 106951;

unsigned compute_checksum(int fd) {
    unsigned sum = 0;
    char buf[32];
    ssize_t res;
    while ((res = read(fd, buf, sizeof(buf))) > 0) {
        for (int i = 0; i != res; ++i) {
            sum += buf[i];
        }
    }

    printf("Checksum %d\n", sum);

    return sum;
}

int main(int argc, char** argv, char** envs) {
    if (argc != 2) {
        exit(1);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("open");
    }
    unsigned checksum = compute_checksum(fd);
    if (checksum != good_checksum) {
        printf("Hack prevented!\n");
        exit(1);
    }

    sleep(10);
    fexecve(fd, argv, envs);

    perror("");
}
