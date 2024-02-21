#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"



void waitForThread(pthread_t thread, void **status) {
    if (pthread_join(thread, status) != 0) {
        printf("Error joining thread");
        exit(EXIT_FAILURE);
    }
}

void initialization(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr) {
    int status = pthread_mutex_init(mutex, attr);

    if (status != 0) {
        char errorMessage[256];
        strerror_r(status, errorMessage, sizeof(errorMessage));
        printf("Error initializing mutex: %s\n", errorMessage);
        exit(EXIT_FAILURE);
    }
}
pthread_t createThread(void *function(void *), void *argument) {
    pthread_t thread;
    int status = pthread_create(&thread, NULL, function, argument);

    if (status != 0) {
        char errorMessage[256];
        strerror_r(status, errorMessage, sizeof(errorMessage));
        printf("Error creating thread: %s\n", errorMessage);
        exit(EXIT_FAILURE);
    }

    return thread;
}
void locking(pthread_mutex_t *mutex) {
    if (pthread_mutex_lock(mutex) != 0) {
        printf("Error locking mutex");
        exit(EXIT_FAILURE);
    }
}



void destruction(pthread_mutex_t *mutex) {
    int status = pthread_mutex_destroy(mutex);

    if (status != 0) {
        char errorMessage[256];
        strerror_r(status, errorMessage, sizeof(errorMessage));
        printf("Error destroying mutex: %s\n", errorMessage);
        exit(EXIT_FAILURE);
    }
}

void unlocking(pthread_mutex_t *mutex) {
    if (pthread_mutex_unlock(mutex) != 0) {
        printf("Error unlocking mutex");
        exit(EXIT_FAILURE);
    }
}
