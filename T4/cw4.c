#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#define CHUNK_SIZE 5

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s input.txt output.txt\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    FILE *fpp = fopen("input.txt", "r");

    // Sprawdź czy plik został otwarty poprawnie
    if (fpp == NULL) {
        printf("Nie udało się otworzyć pliku\n");
        return 1;
    }

    // Odczytaj i wypisz zawartość pliku
    printf("INPUT: ");
    int b;
    while ((b = fgetc(fpp)) != EOF) {
        putchar(b);
    }

    // Zamknij plik
    fclose(fpp);
    printf("\n");

    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Proces potomny - odbiera dane z potoku i zapisuje do pliku

        close(fd[1]); // zamykamy nieużywaną część potoku

        int output_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (output_fd == -1) {
            perror("open output file");
            exit(EXIT_FAILURE);
        }


        char buffer[CHUNK_SIZE];
        ssize_t bytes_read;

        while ((bytes_read = read(fd[0], buffer, CHUNK_SIZE)) > 0) {
            // losowe odczekanie
            srand(time(NULL));
            int sleep_time = rand() % 5;
            sleep(sleep_time);

            // wypisanie odebranych danych na ekran
            printf("[Consumer] Received %ld bytes\n", bytes_read);

            // zapisanie danych do pliku
            ssize_t bytes_written = write(output_fd, buffer, bytes_read);
            if (bytes_written != bytes_read) {
                perror("write output file");
                exit(EXIT_FAILURE);
            }
        }
        // zamknięcie potoku i pliku
        close(fd[0]);
        close(output_fd);

    } else {
        // Proces macierzysty - odczytuje dane z pliku i przesyła do potoku

        close(fd[0]); // zamykamy nieużywaną część potoku

        int input_fd = open(argv[1], O_RDONLY);
        if (input_fd == -1) {
            perror("open input file");
            exit(EXIT_FAILURE);
        }

        char buffer[CHUNK_SIZE];
        ssize_t bytes_read;

        while ((bytes_read = read(input_fd, buffer, CHUNK_SIZE)) > 0) {
            // losowe odczekanie
            srand(time(NULL));
            int sleep_time = rand() % 5;
            sleep(sleep_time);

            // wypisanie przesłanych danych na ekran
            printf("[Producer] Sent %ld bytes\n", bytes_read);

            // przesłanie danych przez potok
            ssize_t bytes_written = write(fd[1], buffer, bytes_read);
            if (bytes_written != bytes_read) {
                perror("write pipe");
                exit(EXIT_FAILURE);
            }
        }
        // zamknięcie potoku i pliku
        close(fd[1]);
        close(input_fd);
    }
              // wypisanie outputu na ekran



    FILE *fp = fopen("output.txt", "r");

// Sprawdź czy plik został otwarty poprawnie
    if (fp == NULL) {
    printf("FAILED TO OPEN\n");
    return 1;
}

// Odczytaj i wypisz zawartość pliku
    printf("OUTPUT: ");
    int c;
    while ((c = fgetc(fp)) != EOF) {
    putchar(c);
}
    fclose(fp);




    return 0;
}
