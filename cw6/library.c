#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Tworzenie semafora o podanej nazwie
sem_t *create_semaphore(const char *name) {
    sem_t *semaphore_address;
    if ((semaphore_address = sem_open(name, O_CREAT | O_EXCL, 0644, 1)) == SEM_FAILED) {
        perror("error creating semaphore");
        exit(EXIT_FAILURE);
    } else {
        return semaphore_address;
    }
}

// Otwieranie semafora o podanej nazwie
sem_t *open_semaphore(const char *name) {
    sem_t *semaphore_address;
    if ((semaphore_address = sem_open(name, 0)) == SEM_FAILED) {
        perror("error opening semaphore");
        exit(EXIT_FAILURE);
    } else {
        return semaphore_address;
    }
}

// Usunięcie semafora o podanej nazwie
void remove_semaphore(const char *name) {
    if (sem_unlink(name) == -1) {
        perror("error removing semaphore");
        exit(EXIT_FAILURE);
    }
}


// Zamykanie semafora
void close_semaphore(sem_t *sem) {
    if (sem_close(sem) == -1) {
        perror("error closing semaphore");
        exit(EXIT_FAILURE);
    }
}



// Zwolnienie semafora
void release_semaphore(sem_t *sem) {
    if (sem_post(sem) == -1) {
        perror("error releasing semaphore");
        exit(EXIT_FAILURE);
    }
}

// Pobieranie wartości semafora
void get_semaphore_value(sem_t *sem, int *sval) {
    if (sem_getvalue(sem, sval) == -1) {
        perror("error getting semaphore value");
        exit(EXIT_FAILURE);
    }
}

// Przechwycenie semafora
void acquire_semaphore(sem_t *sem) {
    if (sem_wait(sem) == -1) {
        perror("error acquiring semaphore");
        exit(EXIT_FAILURE);
    }
}

