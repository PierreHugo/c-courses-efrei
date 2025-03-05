#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define MAX_TRIES 10

int main() {
    int pipefd[2]; // Tube pour la communication père <-> fils
    pid_t pid;
    int secret, guess, tries = 0;

    if (pipe(pipefd) == -1) {
        perror("Erreur lors de la création du tube");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("Erreur lors du fork");
        return 1;
    }

    if (pid == 0) { // Processus fils (joueur)
        close(pipefd[1]); // Fermer l'écriture
        while (1) {
            read(pipefd[0], &guess, sizeof(int));
            if (guess == -1) break;
            printf("[Fils] Mon choix : %d\n", guess);
        }
        close(pipefd[0]);
        printf("*** FIN du processus < %d > ***\n", getpid());
    } else { // Processus père (maître du jeu)
        close(pipefd[0]); // Fermer la lecture
        srand(time(NULL) + getpid());  // Générer une graine unique
        secret = rand() % 100 + 1;
        printf("[Père] Nombre secret généré : %d\n", secret);

        do {
            usleep(100000); // Petite pause pour éviter des nombres trop proches
            guess = rand() % 100 + 1;
            printf("[Père] Proposition : %d\n", guess);
            write(pipefd[1], &guess, sizeof(int));
            tries++;
        } while (guess != secret && tries < MAX_TRIES);

        // Arrêter le fils
        guess = -1;
        write(pipefd[1], &guess, sizeof(int));
        close(pipefd[1]);
        wait(NULL);
        printf("[Père] Fin du jeu après %d essais.\n", tries);
    }
    return 0;
}
