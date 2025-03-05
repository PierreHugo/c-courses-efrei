#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <dispatch/dispatch.h>
#include <unistd.h>

// Mutex et sémaphore pour la synchronisation
pthread_mutex_t mutex;
dispatch_semaphore_t semaphore;

void *thread_1_non_synchro(void *arg) {
    printf("je ");
    printf("mes ");
    return NULL;
}

void *thread_2_non_synchro(void *arg) {
    printf("synchronise ");
    printf("threads\n");
    return NULL;
}

void *thread_1_synchro_mutex(void *arg) {
    pthread_mutex_lock(&mutex);
    printf("je ");
    printf("mes ");
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *thread_2_synchro_mutex(void *arg) {
    pthread_mutex_lock(&mutex);
    printf("synchronise ");
    printf("threads\n");
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *thread_1_synchro_sem(void *arg) {
    dispatch_semaphore_wait(semaphore, DISPATCH_TIME_FOREVER);
    printf("je ");
    printf("mes ");
    dispatch_semaphore_signal(semaphore);
    return NULL;
}

void *thread_2_synchro_sem(void *arg) {
    dispatch_semaphore_wait(semaphore, DISPATCH_TIME_FOREVER);
    printf("synchronise ");
    printf("threads\n");
    dispatch_semaphore_signal(semaphore);
    return NULL;
}

int main() {
    int choix;
    pthread_t t1, t2;
    pthread_mutex_init(&mutex, NULL);
    semaphore = dispatch_semaphore_create(1); // Sémaphore initialisé à 1

    while (1) {
        printf("\nChoix de la version à exécuter :\n");
        printf("1) Sans synchro\n");
        printf("2) Synchro avec mutex\n");
        printf("3) Synchro avec sémaphore\n");
        printf("4) Les 3 versions à la suite\n");
        printf("5) Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        if (choix == 5) break;

        switch (choix) {
            case 1:
                pthread_create(&t1, NULL, thread_1_non_synchro, NULL);
                pthread_create(&t2, NULL, thread_2_non_synchro, NULL);
                pthread_join(t1, NULL);
                pthread_join(t2, NULL);
                break;
            case 2:
                pthread_create(&t1, NULL, thread_1_synchro_mutex, NULL);
                pthread_create(&t2, NULL, thread_2_synchro_mutex, NULL);
                pthread_join(t1, NULL);
                pthread_join(t2, NULL);
                break;
            case 3:
                pthread_create(&t1, NULL, thread_1_synchro_sem, NULL);
                pthread_create(&t2, NULL, thread_2_synchro_sem, NULL);
                pthread_join(t1, NULL);
                pthread_join(t2, NULL);
                break;
            case 4:
                printf("\nSans synchronisation :\n");
                pthread_create(&t1, NULL, thread_1_non_synchro, NULL);
                pthread_create(&t2, NULL, thread_2_non_synchro, NULL);
                pthread_join(t1, NULL);
                pthread_join(t2, NULL);

                printf("\nAvec mutex :\n");
                pthread_create(&t1, NULL, thread_1_synchro_mutex, NULL);
                pthread_create(&t2, NULL, thread_2_synchro_mutex, NULL);
                pthread_join(t1, NULL);
                pthread_join(t2, NULL);

                printf("\nAvec sémaphore :\n");
                pthread_create(&t1, NULL, thread_1_synchro_sem, NULL);
                pthread_create(&t2, NULL, thread_2_synchro_sem, NULL);
                pthread_join(t1, NULL);
                pthread_join(t2, NULL);
                break;
            default:
                printf("Choix invalide !\n");
        }
    }

    pthread_mutex_destroy(&mutex);
    return 0;
}