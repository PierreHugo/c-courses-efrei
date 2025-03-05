#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    printf("-Hello-\n");
    
    pid_t pid = fork();

    if (pid < 0) {
        perror("Erreur lors du fork");
        return 1;
    }

    if (pid > 0) {  // Processus père
        wait(NULL);
        printf("IVS");
    } else {  // Processus fils
        printf("JVL");
    }

    printf("-\n");
    return 0;
}
