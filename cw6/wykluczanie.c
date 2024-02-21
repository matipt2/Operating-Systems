#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include "library.h"
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>

void validate_input(int argc, char* argv[]) {
    // Sprawdzenie poprawności liczby argumentów
    if (argc != 5) {
        printf("Error: incorrect number of arguments!\n");
        printf("To run the program, enter: %s critical_section_count input_file semaphore_name synchronize\n", argv[0]);
        _exit(EXIT_FAILURE);
    }
}


int main(int argc, char *argv[]) {

    const double max_waiting_time = 2.0;
    sem_t *semaphore;
    int semaphore_value;
    


    validate_input(argc, argv);
    int critical_section_count;


    critical_section_count = atoi(argv[1]);
    bool synchronization = atoi(argv[4]);

    int number;
    // Otwieranie semafora, jeśli synchronizacja jest włączona
    if (synchronization) {
        semaphore = open_semaphore(argv[3]);
    }
    int read_result;
    // Pętla krytycznych sekcji
    int i=0;
    int file;
    char message[160];
    while(i<critical_section_count){
        srand(time(NULL));

        // Opóźnienie w sekcji krytycznej
        sleep((double)(rand() % (int)(max_waiting_time * 100)) / 100);
        if (synchronization) {
            get_semaphore_value(semaphore, &semaphore_value);
            printf("PID:%d   CRITICAL SECTION ( BEFORE ):   %d\n", getpid(), semaphore_value);
            acquire_semaphore(semaphore);
        }

        // Otwarcie pliku do odczytu
        if ((file = open(argv[2], O_RDONLY, 0644)) == -1) {
            printf("Error opening file %s for reading", argv[2]);
            perror("File error");
            _exit(EXIT_FAILURE);
        }
        char buffer[120];
        // Odczyt danych z pliku
        read_result = read(file, &buffer, 10);
        if (read_result == -1) {
            printf("Error reading from file\n");
            _exit(EXIT_FAILURE);
        } else if (read_result == 0) {
            break;
        } else {
            buffer[read_result] = '\0';
            get_semaphore_value(semaphore, &semaphore_value);
            sprintf(message, "\t PID:%d   critical section:  %d  number :  %s  semaphore  %d\n", getpid(), i, buffer, semaphore_value);
            printf("**        **        **        **         **         **          **         **        **");
            printf("%s\n", message);
        }
        int number;
        // Zamknięcie pliku
        if (close(file) == -1) {
            perror("Error closing file");
            exit(EXIT_FAILURE);
        }

        // Inkrementacja liczby
        number = atoi(buffer);
        number++;
        sprintf(buffer, "%d", number);
        printf("number %d", number);

        // Opóźnienie po sekcji krytycznej
        sleep((double)(rand() % (int)(max_waiting_time * 100)) / 100);
        if ((file = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1) {
            printf("Error opening file %s for writing", argv[1]);
            perror("File error");
            _exit(EXIT_FAILURE);
        }

    // Otwiera plik o nazwie przekazanej jako argv[2] w trybie zapisu (O_WRONLY) oraz tworzenia nowego pliku jeśli nie istnieje (O_CREAT).
    // Opcja O_TRUNC powoduje, że plik jest opróżniany, jeśli już istnieje.
    //Jeśli otwarcie pliku zwróci wartość równą -1, oznacza to, że wystąpił błąd podczas otwierania pliku.
    //W takim przypadku wyświetlany jest komunikat o błędzie zawierający nazwę pliku, który nie mógł zostać otwarty do zapisu.
        if ((file = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1) {
            printf("Error opening file %s for writing", argv[1]);
            perror("File error");
            _exit(EXIT_FAILURE);
        }

        // Zapis danych do pliku
        if (write(file, &buffer, strlen(buffer)) == -1) {
            perror("Error writing to file");
            _exit(EXIT_FAILURE);
        }

        // Zamknięcie pliku
        if (close(file) == -1) {
            perror("Error closing file");
            exit(EXIT_FAILURE);
        }

        // Zwolnienie semafora, jeśli synchronizacja jest włączona
        if (synchronization) {
            release_semaphore(semaphore);
            get_semaphore_value(semaphore, &semaphore_value);
            printf(" PID   %d CRITICAL SECTION ( AFTER )  VALUE:  %d\n", getpid(), semaphore_value);
        }
        i++;
    }

// Zamknięcie semafora, jeśli synchronizacja jest włączona
    if (synchronization) {
        close_semaphore(semaphore);
    }

    return 0;
}
