#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t forks[N];
sem_t mutex;

void* philosopher(void* arg) {
    int id = *(int*)arg;

    for (int i = 0; i < 2; i++) {
        printf("P %d is thinking\n", id + 1);
        sleep(1);

        sem_wait(&mutex);
        sem_wait(&forks[id]);
        sem_wait(&forks[(id + 1) % N]);
        sem_post(&mutex);

        printf("P %d is granted to eat\n", id + 1);
        sleep(1);
        printf("P %d has finished eating\n", id + 1);

        sem_post(&forks[id]);
        sem_post(&forks[(id + 1) % N]);
    }

    return NULL;
}

int main() {
    pthread_t tid[N];
    int ids[N];

    sem_init(&mutex, 0, 1);
    for (int i = 0; i < N; i++)
        sem_init(&forks[i], 0, 1);

    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&tid[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < N; i++)
        pthread_join(tid[i], NULL);

    return 0;
}
