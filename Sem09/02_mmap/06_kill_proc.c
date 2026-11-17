#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** argv) {
    // Выделяем 5 гб памяти
    size_t size = 7ULL * 1024 * 1024 * 1024;

    char* ptr = malloc(size);

    // Просто пауза, которую мы можем прервать введя символ
    getchar();

    // есть запустим с аргументом командной строки, то тогда память
    // будет заполняться единицами и ее придется физически выделять.
    // Можно в htop посмотреть на свободную память и размер swap файла
    if (argc > 1) {
        for (size_t i = 0; i < size; ++i) {
            ptr[i] = '1';
        }
        printf("success\n");
        getchar();
    }
    // sudo dmesg -T | grep -i -E "out of memory|oom-kill|killed process"
}
