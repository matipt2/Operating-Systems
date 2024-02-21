#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    printf("MACIERZYSTY: \n");
    printf("PID: %d\n", getpid());
    printf("UID: %d\n", getuid());
    printf("GID: %d\n", getgid());
    printf("PPID: %d\n", getppid());
    printf("PGID: %d\n", getpgrp());
    for (int i = 0; i < 3; i++) {
        switch (fork()) {
            // tworzenie procesu potomnego nie powiodlo sie
            case -1:
                perror("fork ERROR");
                exit(1);

            case 0:
                // ustawienie PGID procesu potomnego na PGID procesu macierzystego
                if (setpgid(0, 0) == -1) {
                    perror("setpgid ERROR");
                    exit(1);
                }
                printf("#############\n");
                printf("Potomny PID: %d\n", getpid());
                printf("Potomny UID: %d\n", getuid());
                printf("Potomny GID: %d\n", getgid());
                printf("Potomny PPID: %d\n", getppid());
                printf("Potomny PGID: %d\n", getpgrp());
                break;

            default:
                // oczekiwanie na zakończenie procesu potomnego
                wait(NULL);
                break;
        }
    }

    return 0;

}

