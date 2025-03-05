#include <stdio.h>
#include <unistd.h>

int main(void) {
    for(int i = 0; i < 3; i++) {
        fork();
    }

    printf("hello | PID = %d | PPID = %d\n", getpid(), getppid());
    return 0;
}
