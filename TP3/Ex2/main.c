#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 3 // Nombre de threads du groupe

pthread_mutex_t mutex;
pthread_cond_t condition;
int count = 0;

void *thread_groupe(void *arg) {
    int id = *(int *)arg;
    sleep(rand() % 3 + 1);
    printf("[Thread %d] Point atteint\n", id);

    pthread_mutex_lock(&mutex);
    count++;
    if (count == N) {
        pthread_cond_signal(&condition);
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *thread_barriere(void *arg) {
    sleep(rand() % 3 + 1);
    printf("[Thread Barrière] Barrière atteinte, en attente...\n");
    
    pthread_mutex_lock(&mutex);
    while (count < N) {
        pthread_cond_wait(&condition, &mutex);
    }
    pthread_mutex_unlock(&mutex);
    
    printf("[Thread Barrière] Je peux continuer !\n");
    return NULL;
}

int main() {
    pthread_t threads[N], t_barriere;
    int ids[N];
    
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&condition, NULL);
    
    srand(time(NULL));
    pthread_create(&t_barriere, NULL, thread_barriere, NULL);
    
    for (int i = 0; i < N; i++) {
        ids[i] = i + 1;
        pthread_create(&threads[i], NULL, thread_groupe, &ids[i]);
    }
    
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_join(t_barriere, NULL);
    
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condition);
    
    return 0;
}
