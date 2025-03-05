#include <stdio.h>
#include <unistd.h>

int main(void) {
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("Erreur lors du fork");
        return 1;
    }

    printf("hello | PID = %d | PPID = %d\n", getpid(), getppid());
    return 0;
}
