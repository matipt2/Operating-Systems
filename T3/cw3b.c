#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>


int main(int argc, char *argv[]) {
// sprawdzenie czy ilość argumentów jest poprawna
if (argc != 4) {
fprintf(stderr, "Usage: %s [default|ignore|custom] [signal_number] [child_program]\n", argv[0]);
return 1;
}

// odczytanie argumentów wejściowych
char *mode = argv[1];
int signal_number = atoi(argv[2]);
char *programa = argv[3];

// utworzenie procesu potomnego
pid_t pid = fork();
if (pid == -1) { // błąd
    perror("fork");
    return 1;
} else if (pid == 0) { // proces potomny
    // uruchomienie programu z argumentami
    execl(programa, programa, mode, argv[2], NULL);
    perror("execl"); // wyświetlenie błędu w przypadku niepowodzenia
    exit(1);
} else { // proces macierzysty
    sleep(1); // oczekiwanie stworzenie procesu potomnego

    // sprawdzenie czy proces potomny istnieje
    int status;
    if (kill(pid, 0) == -1) { // kill(pid, 0) - wysłanie sygnału 0 (zero) do procesu potomnego
        perror("kill"); // błąd
        return 1;
    }

    // wysłanie sygnału do procesu potomnego
    if (kill(pid, signal_number) == -1) {
        perror("kill"); // błąd
        return 1;
    }

    // oczekiwanie na zakończenie procesu potomnego
    if (wait(&status) == -1) {
        perror("wait"); // błąd
        return 1;
    }

    // sprawdzenie czy proces potomny zakończył się przez sygnał
    if (WIFSIGNALED(status)) { // true jeśli proces zakończony z powodu sygnału
        int sig_num = WTERMSIG(status);// numer sygnału
        printf("Child process terminated due to signal %d: %s\n", sig_num, (char *)strsignal(sig_num)); // wyświetlenie informacji
    }
}

return 0;
}
