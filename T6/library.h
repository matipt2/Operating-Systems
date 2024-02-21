#ifndef SEMAFORY_H
#define SEMAFORY_H

sem_t *open_semaphore(const char *name);
void close_semaphore(sem_t *sem);
sem_t *create_semaphore(const char *name);
void get_semaphore_value(sem_t *sem, int *sval);
void remove_semaphore(const char *name);
void release_semaphore(sem_t *sem);
void acquire_semaphore(sem_t *sem);

#endif