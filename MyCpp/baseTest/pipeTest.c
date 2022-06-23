#include <stdio.h>
#include <string.h>
#include <unistd.h>

// pipe test from child and father program
// platform: Linux

int main() {
    int pipefd[2] = {0};
    pipe(pipefd);
    pid_t id = fork();

    if (id == 0) {
        // child program
        close(pipefd[0]);
        const char* msg = "I am a child\n";
        int count = 0;
        while (1) {
            write(pipefd[1], msg, strlen(msg));
            printf("child:%d\n", count++);
            sleep(3);
        }
    } else {
        // father program
        close(pipefd[1]);
        char buffer[64];
        while (1) {
            ssize_t s = read(pipefd[0], buffer, sizeof(buffer) - 1);
            if (s > 0) {
                printf("father massage : %s\n", buffer);
            }
        }
    }
    return 0;
}
