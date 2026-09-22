#include <stdlib.h>
#include <stdio.h>

size_t get_allocated_size(void *ptr) {
    return *((size_t *)ptr - 1);
}

int main() {

    void* p = malloc(10000);
    printf("%p\n", p);
    printf("%ld\n", get_allocated_size(p));
    void* p2 = realloc(p, 10001);
    if (p2 == NULL) {
        perror("realloc");
        exit(1);
    }
    printf("%ld\n", get_allocated_size(p2));
    printf("%p\n", p2);

}
