#define _GNU_SOURCE

#include <signal.h>
#include <stdio.h>
#include <sys/signalfd.h>
#include <unistd.h>

int main(void) {
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    if (sigprocmask(SIG_BLOCK, &mask, NULL) == -1) {
        perror("sigprocmask");
        return 1;
    }

    int fd = signalfd(-1, &mask, SFD_CLOEXEC);
    if (fd == -1) {
        perror("signalfd");
        return 1;
    }

    printf("PID: %ld\n", (long)getpid());

    struct signalfd_siginfo info;
    ssize_t bytes = read(fd, &info, sizeof(info));
    if (bytes == -1) {
        perror("read");
        return 1;
    }
    printf("Signal: %u, sender PID: %u\n",
           (unsigned)info.ssi_signo, (unsigned)info.ssi_pid);
    close(fd);
    return 0;
}
