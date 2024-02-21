#include <pthread.h>

void unlocking(pthread_mutex_t *mutex);
pthread_t createThread(void *function(void *), void *argument);
void initialization(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
void waitForThread(pthread_t thread, void **status);
void locking(pthread_mutex_t *mutex);
void destruction(pthread_mutex_t *mutex);
