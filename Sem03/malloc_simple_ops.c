#include <stdio.h>
#include <stdlib.h>

typedef struct s {
    int i;
    char c;
} MyStruct;

int main() {
    printf("%ld\n", sizeof(MyStruct));

    int num = 10;

    MyStruct* p = calloc(sizeof(*p), num);
    if (p == NULL) {
        perror("malloc");
        exit(1);
    }

    for (int i = 0; i < num; ++i) {
        (p+i)->i = i * i;
        (p+i)->c = 'a' + i;
    }

    for (int i = 0; i < num; ++i) {
        printf("%d, %c\n", p[i].i, p[i].c);
    }


    MyStruct *tmp = realloc(p, sizeof(*p) * num * 2);
    if (tmp == NULL) {
        perror("realloc");
        free(p);
        exit(1);
    }
    p = tmp;

    for (int i = num; i < num * 2; ++i) {
        (p+i)->i = i;
        (p+i)->c = 'a' + i;
    }


    for (int i = 0; i < num * 2; ++i) {
        printf("%d, %c\n", p[i].i, p[i].c);
    }

    free(p);
}
