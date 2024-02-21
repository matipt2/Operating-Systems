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
            case -1:
                perror("fork ERROR");
                exit(1);

            case 0:
                printf("##############\n");
                execlp("./identyfikatory.x", "identyfikatory", NULL); // wywołanie programu "identyfikatory"
                perror("execlp ERROR"); // jeśli wywołanie nie powiedzie się, wypisz błąd
                exit(1);
            default:
                wait(NULL);
                break;
        }
    }
    return 0;
}
