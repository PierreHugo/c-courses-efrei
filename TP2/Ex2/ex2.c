#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define N 5  // Nombre d'itérations

int globale = 1; // Variable globale partagée

int main() {
    pid_t pid;

    printf("[Début] PID = %d | PPID = %d | globale = %d\n", getpid(), getppid(), globale);

    pid = fork();

    if (pid < 0) {
        perror("Erreur lors du fork");
        return 1;
    }

    if (pid == 0) {  // Processus fils
        printf("[Fils] PID = %d | PPID = %d | globale = %d\n", getpid(), getppid(), globale);
        for (int i = 1; i <= N; i++) {
            globale *= 2;
            printf("[Fils] i = %d | globale = %d\n", i, globale);
        }
        printf("*** FIN du processus < %d > | globale = %d ***\n", getpid(), globale);
    } else {  // Processus père
        printf("[Père] PID = %d | PPID = %d | globale = %d\n", getpid(), getppid(), globale);
        for (int i = 1; i <= N; i++) {
            globale += 10;
            printf("[Père] i = %d | globale = %d\n", i, globale);
        }
        wait(NULL); // Attendre la fin du fils
        printf("*** FIN du processus < %d > | globale = %d ***\n", getpid(), globale);
    }

    return 0;
}
