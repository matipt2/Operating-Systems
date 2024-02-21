#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
void signal_handler(int signal_number) {
    printf("Przechwycono sygnał nr %d.\n", signal_number);
}

int main(int argc, char *argv[]) {
    int signal_number, mode;

    if (argc < 3) {
        printf("Sposób użycia: %s tryb sygnał\n", argv[0]);
        printf("Tryby: 0 - akcja domyślna, 1 - ignorowanie, 2 - własna obsługa\n");
        return 1;
    }

    mode = atoi(argv[1]);
    signal_number = atoi(argv[2]);

    printf("Mój PID to %d.\n", getpid());

    switch (mode) {
        case 0:
            signal(signal_number, SIG_DFL); // ustaw akcję domyślną
            break;
        case 1:
            signal(signal_number, SIG_IGN); // zignoruj sygnał
            break;
        case 2:
            signal(signal_number, signal_handler); // zdefiniuj własną obsługę
            break;
        default:
            printf("Nieznany tryb pracy.\n");
            return 1;
    }

    pause(); // czekaj na sygnał

    return 0;
}
