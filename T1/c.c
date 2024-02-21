#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    printf("###########\n");
    printf("Macierzysty\n");
    printf("PID: %d\n", getpid());
    printf("UID: %d\n", getuid());
    printf("GID: %d\n", getgid());
    printf("PPID: %d\n", getppid());
    printf("PGID: %d\n", getpgrp());
    for (int i = 0; i < 3; i++) {

        switch (fork()) {
            case -1:
                perror("fork ERROR");
                exit(1);

            case 0:
                sleep(2);
                printf("\n");
                printf("Potomny PID: %d\n", getpid());
                printf("Potomny UID: %d\n", getuid());
                printf("Potomny GID: %d\n", getgid());
                printf("Potomny PPID: %d\n", getppid());
                printf("Potomny PGID: %d\n", getpgrp());
                break;

            default:
                break;
        }
    }

    return 0;
}
