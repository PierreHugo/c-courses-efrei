#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 5 // Nombre de philosophes

pthread_mutex_t baguettes[N];

void penser(int id) {
    printf("[Philosophe %d] Pense...\n", id);
    usleep(rand() % 1000000);
}

void manger(int id) {
    printf("[Philosophe %d] Mange...\n", id);
    usleep(rand() % 1000000);
}

void *philosophe(void *arg) {
    int id = *(int *)arg;
    int gauche = id;
    int droite = (id + 1) % N;

    while (1) {
        penser(id);

        // Prendre les baguettes (éviter l'interblocage)
        if (id % 2 == 0) {
            pthread_mutex_lock(&baguettes[gauche]);
            pthread_mutex_lock(&baguettes[droite]);
        } else {
            pthread_mutex_lock(&baguettes[droite]);
            pthread_mutex_lock(&baguettes[gauche]);
        }

        manger(id);

        // Relâcher les baguettes
        pthread_mutex_unlock(&baguettes[gauche]);
        pthread_mutex_unlock(&baguettes[droite]);
    }
    return NULL;
}

int main() {
    pthread_t threads[N];
    int ids[N];
    srand(time(NULL));

    // Initialiser les mutex
    for (int i = 0; i < N; i++) {
        pthread_mutex_init(&baguettes[i], NULL);
    }

    // Créer les threads des philosophes
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, philosophe, &ids[i]);
    }

    // Attendre indéfiniment (simulation continue)
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    // Détruire les mutex (ne sera jamais atteint)
    for (int i = 0; i < N; i++) {
        pthread_mutex_destroy(&baguettes[i]);
    }
    return 0;
}
