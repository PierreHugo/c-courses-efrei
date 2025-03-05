#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    char prenom[50];
    
    printf("Entrez un prénom : ");
    scanf("%s", prenom);
    
    pid = fork();
    
    if (pid < 0) {
        perror("Erreur lors du fork");
        return 1;
    }
    
    if (pid == 0) { // Processus fils
        printf("[Fils] PID = %d | PPID = %d\n", getpid(), getppid());
        execlp("echo", "echo", "Bonjour", prenom, NULL);
        perror("Erreur lors de l'exécution de execlp"); // S'affiche si execlp échoue
        return 1;
    } else { // Processus père
        wait(NULL); // Attendre la fin du fils
        printf("[Père] Mon fils a terminé son exécution.\n");
    }
    
    return 0;
}
