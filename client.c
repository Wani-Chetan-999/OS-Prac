#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

sem_t mutex, wrt;
int data = 0, rcnt = 0;

void* reader(void* arg) {
    sem_wait(&mutex);
    rcnt++;
    if (rcnt == 1) {
        sem_wait(&wrt); // First reader locks writer access
    }
    sem_post(&mutex);

    printf("Reader %ld: Data is %d\n", (long)arg, data);
    sleep(1);

    sem_wait(&mutex);
    rcnt--;
    if (rcnt == 0) {
        sem_post(&wrt); // Last reader unlocks writer access
    }
    sem_post(&mutex);

    return NULL;
}

void* writer(void* arg) {
    sem_wait(&wrt); // Lock for writers

    data++;
    printf("Writer %ld: Data is written as %d\n", (long)arg, data);
    sleep(1);

    sem_post(&wrt); // Unlock for writers

    return NULL;
}

int main() {
    int i;
    pthread_t rtid[5], wrtid[5];

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    // Create reader and writer threads
    for (i = 0; i < 5; i++) {
        pthread_create(&wrtid[i], NULL, writer, (void*)(long)i);
        pthread_create(&rtid[i], NULL, reader, (void*)(long)i);
    }

    // Wait for all threads to complete
    for (i = 0; i < 5; i++) {
        pthread_join(wrtid[i], NULL);
        pthread_join(rtid[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
