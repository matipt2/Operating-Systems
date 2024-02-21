#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>



int main() {
    printf("PID: %d\n", getpid());
    printf("UID: %d\n", getuid());
    printf("GID: %d\n", getgid());
    printf("PPID: %d\n", getppid());
    printf("PGID: %d\n", getpgrp());
    return 0;
}
