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
// jeśli iteracja jest pierwsza (i = 0), wypisuje informacje o procesie nadrzędnym
        if (i == 0) {

        }
// switch, który tworzy proces potomny
        switch (fork()) {
            case -1:
                perror("fork ERROR"); // jeśli utworzenie procesu potomnego nie powiedzie się, wypisz błąd
                exit(1);

            case 0:  // jeśli jest to proces potomny, wypisze znowu identyfikatory
                printf("##############\n");
                printf("Potomny PID: %d\n", getpid());
                printf("Potomny UID: %d\n", getuid());
                printf("Potomny GID: %d\n", getgid());
                printf("Potomny PPID: %d\n", getppid());
                printf("Potomny PGID: %d\n", getpgrp());
            default:
                wait(NULL);  // czekaj na proces potomny
                break;
        }
    }
    return 0;
}
