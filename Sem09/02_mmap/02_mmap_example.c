#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "expected filename\n");
        return 1;
    }

    int fd = open(argv[1], O_RDWR | O_CREAT, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    struct stat st;
    if (fstat(fd, &st) < 0) {
        perror("fstat");
        return 1;
    }
    if (st.st_size == 0) {
        close(fd);
        return 0;
    }

    size_t size = (size_t)st.st_size;
    char *data = mmap(NULL, size, PROT_WRITE, MAP_SHARED, fd, 0);
    if (data == MAP_FAILED) {
        perror("mmap");
        return 1;
    }
    close(fd);

    for (size_t i = 0; i < size; ++i) {
        data[i] = '2';
    }

    if (munmap(data, size) < 0) {
        perror("munmap");
        return 1;
    }
    return 0;
}
