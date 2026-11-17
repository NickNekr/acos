#define _POSIX_C_SOURCE 200809L

#include <signal.h>
#include <stdio.h>
#include<unistd.h>

volatile sig_atomic_t counter;

void handler(int signo) {
    (void)signo;
    counter = 100;
}

int main(void) {
    struct sigaction sa = {0};
    sa.sa_handler = handler;
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    sig_atomic_t old = counter;
    printf("main read: %d\n", (int)old);

    sleep(5);

    printf("after handler: %d\n", (int)counter);

    counter = old + 1;
    printf("main wrote: %d\n", (int)counter);
    return 0;
}
