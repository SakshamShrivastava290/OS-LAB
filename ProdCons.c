#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5
int buffer[SIZE], in = 0, out = 0;

sem_t mutex, empty, full;

void* producer(void* arg) {
    for (int i = 0; i < 3; i++) {
        sem_wait(&empty);     // Wait if buffer is full
        sem_wait(&mutex);     // Lock buffer

        int item = rand() % 100 + 1;
        buffer[in] = item;    // Add item to buffer
        printf("Producer has produced: Item %d\n", item);
        in = (in + 1) % SIZE; // Circular buffer

        sem_post(&mutex);     // Unlock buffer
        sem_post(&full);      // One more item in buffer
        sleep(1);             // Simulate delay
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 0; i < 3; i++) {
        sem_wait(&full);      // Wait if buffer is empty
        sem_wait(&mutex);     // Lock buffer

        int item = buffer[out]; 
        printf("Consumer has consumed: Item %d\n", item);
        buffer[out] = 0;      // Optional: clear slot
        out = (out + 1) % SIZE; // Circular buffer

        sem_post(&mutex);     // Unlock buffer
        sem_post(&empty);     // One more empty slot
        sleep(1);             // Simulate delay
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    sem_init(&mutex, 0, 1);   // Binary semaphore (mutex)
    sem_init(&empty, 0, SIZE); // Initially all slots are empty
    sem_init(&full, 0, 0);    // No items at the start

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
