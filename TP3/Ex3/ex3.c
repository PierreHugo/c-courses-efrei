#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_ITERATIONS 10

char buffer[BUFFER_SIZE];
int in = 0, out = 0;
int count = 0;

pthread_mutex_t mutex;
pthread_cond_t buffer_not_empty, buffer_not_full;

void *producer(void *arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        char item = 'A' + (rand() % 26);
        pthread_mutex_lock(&mutex);
        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&buffer_not_full, &mutex);
        }
        buffer[in] = item;
        printf("[Producteur] Produit: %c\n", item);
        in = (in + 1) % BUFFER_SIZE;
        count++;
        pthread_cond_signal(&buffer_not_empty);
        pthread_mutex_unlock(&mutex);
        usleep(500000);
    }
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        pthread_mutex_lock(&mutex);
        while (count == 0) {
            pthread_cond_wait(&buffer_not_empty, &mutex);
        }
        char item = buffer[out];
        printf("[Consommateur] Consommé: %c\n", item);
        out = (out + 1) % BUFFER_SIZE;
        count--;
        pthread_cond_signal(&buffer_not_full);
        pthread_mutex_unlock(&mutex);
        usleep(500000);
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&buffer_not_empty, NULL);
    pthread_cond_init(&buffer_not_full, NULL);

    srand(time(NULL));
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&buffer_not_empty);
    pthread_cond_destroy(&buffer_not_full);

    return 0;
}
