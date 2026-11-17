#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

typedef struct {
    int id;
    char name[50];
    double value;
} Data;

int main(void) {
    const char *filename = "data.bin";

    int fd = open(filename, O_RDWR | O_CREAT, 0666);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    size_t dataSize = sizeof(Data);
    if (ftruncate(fd, dataSize) == -1) {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    Data* mapped = mmap(NULL, dataSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }
    close(fd);

    *mapped = (Data){42, "Hello world", 3.14159};
    // mapped->id = 52;

    if (munmap(mapped, dataSize) == -1) {
        perror("munmap");
        exit(1);
    }

    // ------
    // return 0;

    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(1);
    }
    mapped = mmap(NULL, dataSize, PROT_READ, MAP_SHARED, fd, 0);
    if (mapped == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }
    close(fd);

    printf("id: %d\n", mapped->id);
    printf("name: %s\n", mapped->name);
    printf("value: %f\n", mapped->value);

    if (munmap(mapped, dataSize) == -1) {
        perror("munmap");
        exit(1);
    }
    return 0;
}
