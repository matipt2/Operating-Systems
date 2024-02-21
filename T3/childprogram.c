#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#define NUMBER_OF_CHILDREN 10

int main(int argc, char *argv[]) {

    if (argc != 4) {
        printf("Sposób użycia: %s tryb sygnał\n", argv[0]);
        printf("Tryby: 0 - akcja domyślna, 1 - ignorowanie, 2 - własna obsługa\n");
        return 0;
    }

    char *mode = argv[2];
    char *signal_number = argv[3];
    char *programa = argv[1];

    for (int i=0; i<NUMBER_OF_CHILDREN; i++) {
        pid_t pid = fork();
        if (pid == -1) { // błąd
            perror("fork");
            return 1;
        } else if (pid == 0) { // proces potomny
            // uruchomienie programu z argumentami
            execlp(programa, programa, mode, signal_number, NULL);
            perror("execl"); // wyświetlenie błędu w przypadku niepowodzenia
            exit(1);
        }
    }

    signal(atoi(signal_number), SIG_IGN);

    int status;
    pid_t child_pid;
    while ((child_pid = waitpid(-1, &status, 0)) > 0) {
        if (WIFSIGNALED(status)) {
            printf("Child %d exited due to signal %d\n", child_pid, WTERMSIG(status));
        }
    }

    return 0;
}


