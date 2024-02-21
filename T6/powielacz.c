#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include "library.h"
#include <time.h>
#include <stdbool.h>

#define PATH "./" // Ścieżka do pliku

char semaphore_name[20];
bool synchronization;

void exit_handler(void) {
    if (synchronization) {
        remove_semaphore(semaphore_name); // Usuwanie semafora
    }
}

void exit_signal_handler(int signal) {
    if (synchronization) {
        printf("Interrupt signal received, removing the semaphore.\n"); // Sygnał przerwania otrzymany, usuwanie semafora
        remove_semaphore(semaphore_name); // Usuwanie semafora
    }
    _exit(EXIT_SUCCESS);
}


void validate_input(int argc, char* argv[]) {
    if (argc != 7) {
        printf("Incorrect number of arguments!\n");
        printf("To run the program, use: %s subprogram_name num_incrementors num_critical_sections file_in_out semaphore_name synchronization\n", argv[0]);
        exit(EXIT_FAILURE);
    }
}

void validate_atexit() {
    if (atexit(exit_handler) != 0) {
        perror("atexit error");
        exit(EXIT_FAILURE);
    }
}

void validate_signal_setup() {
    if (signal(SIGINT, exit_signal_handler) == SIG_ERR) {
        perror("Signal error");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    validate_input(argc, argv);
    validate_atexit();
    validate_signal_setup();

    int stat_lock;
    int num_incrementors;
    int file;

    char temp[strlen(PATH) + strlen(argv[1]) + 1]; // Tworzenie bufora tymczasowego

    num_incrementors = atoi(argv[2]); // Pobieranie liczby inkrementorów

    strcpy(semaphore_name, argv[5]); // Kopiowanie nazwy semafora

    if (atoi(argv[6]) == 0) {
        synchronization = false;
    }
    else {
        synchronization = true;
    }

    if ((file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1) {
        printf("Error opening file %s for writing", argv[1]);
        perror("File error");
        exit(EXIT_FAILURE);
    }

    if (write(file, "0", 2) == -1) {
        perror("Error writing to file");
        exit(EXIT_FAILURE);
    }

    if (close(file) == -1) {
        perror("Error closing file");
        exit(EXIT_FAILURE);
    }

    if (synchronization) {
        sem_t *semaphore = create_semaphore(semaphore_name); // Tworzenie semafora
        int semaphore_value;
        get_semaphore_value(semaphore, &semaphore_value); // Pobieranie wartości semafora
        printf("Semaphore %s (%p) created with value %d\n", semaphore_name, (void *)semaphore, semaphore_value); // Wyświetlanie informacji o semaforze
    }
    int j=0;
    
    while(j<num_incrementors) {

        switch (fork()) {
            case -1:
                perror("Fork error");
                exit(EXIT_FAILURE);
            case 0:
                sprintf(temp, "%s%s", PATH, argv[1]); // Formatowanie ścieżki do inkrementora
                execl(temp, argv[1], argv[3], argv[4], argv[5], argv[6], NULL); // Wykonanie inkrementora
                perror("Execl error");
                exit(EXIT_FAILURE);
                break;
            default:
                // Kod procesu macierzystego
                break;
        }
        j++;
    }

// Oczekiwanie na zakończenie procesów potomnych przy użyciu funkcji wait.
// Pętla wykonuje się `num_incrementors` razy.
    int k=0;
    
    while(k<num_incrementors){
        if (wait(&stat_lock) == -1) { // Wywołanie funkcji wait, oczekiwanie na zakończenie procesu potomnego
            perror("Wait error");
            exit(EXIT_FAILURE);
        }
        k++;
    }

// Otwieranie pliku w trybie do odczytu.
// Nazwa pliku jest pobierana z `argv[4]`.
// Jeśli otwarcie pliku nie powiedzie się, wyświetlany jest błąd i program kończy działanie.
    int read_result;
    char buffer[10];

    if ((file = open(argv[4], O_RDONLY, 0644)) == -1) {
        printf("Error opening file %s for reading", argv[4]);
        perror("File error");
        exit(EXIT_FAILURE);
    }

// Odczyt danych z pliku do bufora `buffer`.
// Wartość zwracana przez funkcję `read` informuje o ilości odczytanych bajtów lub błędzie.
    read_result = read(file, &buffer, 10);
    if (read_result == -1) { // Błąd odczytu z pliku
        printf("Error reading from file\n");
        exit(EXIT_FAILURE);
    }
    else if (read_result == 0) { // Plik jest pusty
        printf("The file is empty! Something went wrong!\n");
        exit(EXIT_FAILURE);
    }
    else {
        buffer[read_result] = '\0'; 
        // Porównanie wartości w buforze z oczekiwaną wartością (`num_incrementors * atoi(argv[3])`).
        // Wyświetlenie odpowiedniego komunikatu w zależności od wyniku porównania.
        if (atoi(buffer) == (atoi(argv[2]) * atoi(argv[3]))) {
            printf("\nNumber in the file: %s, Incrementation SUCCESS! \n", buffer);
        }
        else {
            printf("\nIncrementation FAILED! Number in the file: %s, expected: %d\n", buffer, (atoi(argv[2]) * atoi(argv[3])));
        }
    }

// Zamykanie pliku.
// Jeśli zamknięcie pliku nie powiedzie się, wyświetlany jest błąd.
    if (close(file) == -1) {
        perror("Error closing file");
        exit(EXIT_FAILURE);
    }

    return 0;
}
