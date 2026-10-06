#include <stdio.h>

int initialized = 97;
int zero = 0;
int buffer[1000];
const char hello[] = "Hello";
const char world[] = "World";

int main(void) {
    buffer[0] = initialized;
    printf("%s\n", hello);
    return 0;
}
