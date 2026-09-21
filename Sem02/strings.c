#include <stdio.h>
#include <string.h>

int main() {
    char hello[12] = "Hello world!";

    printf("sizeof(hello): %ld\n", sizeof(hello));
    printf("strlen(hello): %ld\n", strlen(hello));

    printf("%s\n", hello);


    char* hello2 = "Hello world!";

    printf("sizeof(hello2): %ld\n", sizeof(hello2));
    printf("strlen(hello2): %ld\n", strlen(hello2));

    
    hello2[0] = 'a';
}
