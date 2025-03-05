#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid;
    int sleep_time;
    
    pid = fork();

    if (pid < 0) {
        perror("Erreur lors du fork");
        return 1;
    }

    if (pid == 0) { // Processus fils
        sleep_time = rand() % 5 + 1; // Durée d'attente aléatoire entre 1 et 5 secondes
        printf("[Fils] Je m'endors pour %ds...\n", sleep_time);
        sleep(sleep_time);
        printf("[Fils] Je suis réveillé !\n");
        printf("*** FIN du processus < %d > ***\n", getpid());
    } else { // Processus père
        printf("[Père] En attente du réveil de son fils...\n");
        wait(NULL); // Attendre la fin du fils
        printf("[Père] Mon fils s'est réveillé !\n");
        printf("*** FIN du processus < %d > ***\n", getpid());
    }

    return 0;
}
