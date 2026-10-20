#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

struct Data {
    int id;
    double value;
};

int main(int argc, char* argv[]) {
    // argv[0] = "./a.out"
    if (argc < 2) {
        fprintf(stderr, "expected filename\n");
        exit(1);
    }
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("Failed to open file");
        return 1;
    }


    struct Data res;
    while (read(fd, &res, sizeof res) > 0) {
        printf("%d %.2f\n", res.id, res.value);
    }

    close(fd);

    return 0;
}

