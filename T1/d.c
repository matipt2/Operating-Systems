#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
        printf("Macierzysty:\n");
        printf("PID: %d\n", getpid());
        printf("UID: %d\n", getuid());
        printf("GID: %d\n", getgid());
        printf("PPID: %d\n", getppid());
        printf("PGID: %d\n", getpgrp());

    for(int i=0;i<3;i++) {

        switch (fork()) {  // funkcja fork() tworzy nowy proces potomny, który jest kopią procesu rodzica
            case -1:   // przypadek, gdy funkcja fork() zwraca błąd
                perror("fork ERROR");
                exit(1);
            case 0: // przypadek, gdy proces potomny został poprawnie utworzony
                sleep(i);
                printf("############## ITERACJA: %d\n", i);   // separator między informacjami procesu rodzica i potomnego
                printf("Potomny PID: %d\n", getpid());
                printf("PotomnyUID: %d\n", getuid());
                printf("Potomny GID: %d\n", getgid());
                printf("Potomny PPID: %d\n", getppid());
                printf("Potomny PGID: %d\n", getpgrp());
                break;
            default:   // przypadek, gdy proces rodzica kontynuuje działanie
                sleep(i+1);   // opóźnienie procesu rodzica przed utworzeniem kolejnego procesu potomnego
                break;
        }
    }


    return 0;
}
