#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum { PAGE_BYTES = 4096 };

static void print_address(const char *name, int *p) {
    uintptr_t va = (uintptr_t)p;
    unsigned offset = (unsigned)(va & 0xfff);

    printf("%s: virtual=%p\n", name, (void *)p);
    printf("  PML4=%u PDPT=%u PD=%u PT=%u offset=%u\n",
           (unsigned)((va >> 39) & 0x1ff),
           (unsigned)((va >> 30) & 0x1ff),
           (unsigned)((va >> 21) & 0x1ff),
           (unsigned)((va >> 12) & 0x1ff), offset);
}

int main(void) {
    int *a = malloc(2 * PAGE_BYTES);
    if (!a) {
        perror("malloc");
        return 1;
    }

    int *b = (int *)((unsigned char *)a + PAGE_BYTES - 700);
    *(int *)a = 42;
    *(int *)b = 43;

    print_address("a", a);
    print_address("b", b);

    int *c = (int *)((char *)a + 1);
    print_address("c", c);




    free(a);
    return 0;
}
