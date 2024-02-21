#include <pthread.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "library.h"
#include <unistd.h>


#define NUM_THREADS argv[1]
#define NUM_SECTIONS argv[2]

void moveCursor(unsigned x, unsigned y) {
    printf("\033[%d;%dH\033[2K", y, x);
}

typedef struct {
    int threadNumber;
    int numSections;
} ThreadArgs;

pthread_mutex_t mutex;  // Mutex do synchronizacji wątków
pthread_t *threads;     // Tablica identyfikatorów wątków
int counter;            // Licznik
int numThreads;         // Liczba wątków

void *threadFunction(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    printf("Thread |%d| ID | %p |\n", args->threadNumber, (void *)threads[args->threadNumber]);
    srand(time(NULL));
    sleep(rand() % 3);

    for (int i = 0; i < args->numSections; i++) {
        moveCursor(0, 4 + numThreads + args->threadNumber);
        printf("\033[32mThread |%d| PS |%d|  Number |%d| \033[0m\n", args->threadNumber, i, counter);
        sleep(rand() % 3);

        // Sekcja krytyczna
        locking(&mutex);  // Blokowanie mutexa przed dostępem do sekcji krytycznej
        moveCursor(25, 4 + numThreads + args->threadNumber);
        printf("\033[32mThread |%d| PS |%d|  Number |%d| \033[0m\n", args->threadNumber, i, counter);
        int tempCounter = counter;
        tempCounter++;
        sleep(2);
        counter = tempCounter;
        unlocking(&mutex);  // Odblokowanie mutexa po zakończeniu sekcji krytycznej
        // Koniec sekcji krytycznej

        moveCursor(0, 4 + numThreads + args->threadNumber);
        printf("\033[32mThread |%d| PS |%d|  Number |%d| \033[0m\n", args->threadNumber, i, counter);
        sleep(rand() % 3);
    }
}

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Invalid number of arguments");
        exit(EXIT_FAILURE);
    }

    numThreads = atoi(NUM_THREADS);
    int numSections = atoi(NUM_SECTIONS);

    ThreadArgs *args = (ThreadArgs *)malloc(sizeof(ThreadArgs) * numThreads);
    if (args == NULL) {
        printf("Failed to allocate memory for thread arguments\n");
        exit(EXIT_FAILURE);
    }

    threads = (pthread_t *)malloc(sizeof(pthread_t) * numThreads);
    if (threads == NULL) {
        printf("Failed to allocate memory for thread IDs\n");
        exit(EXIT_FAILURE);
    }

    initialization(&mutex, NULL);  // Inicjalizacja mutexa

    printf("Mutex Address |%p|\n", (void *)&mutex);

    for (int i = 0; i < numThreads; i++) {
        args[i].threadNumber = i;
        args[i].numSections = numSections;
        threads[i] = createThread(threadFunction, (void *)&args[i]);
    }

    for (int i = 0; i < numThreads; i++) {
        waitForThread(threads[i], NULL);
    }

    destruction(&mutex);  // Zniszczenie mutexa

    free(threads);
    free(args);

    moveCursor(0, 4 + 2 * numThreads);
    int expected = numThreads * numSections;

    if (counter == expected) {
        printf("Received number matches the expected value: %d\n", expected);
        printf("------  Synchronization successful  ------.");
    } else {
        printf("Synchronization failed. Received number is %d, expected %d\n", counter, expected);
    }

    return 0;
}
