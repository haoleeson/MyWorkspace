#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define PATHNAME "myPathName"
#define PROJ_ID 132
#define SIZE 4096

int main() {
    key_t k = ftok(PATHNAME, PROJ_ID);
    printf("key : %d\n", k);
    int shmid = shmget(k, SIZE, IPC_CREAT | IPC_EXCL | 0666);

    if (shmid < 0) {
        perror("shmget error\n");
        return 1;
    }
    char* tmp = (char*)shmat(shmid, NULL, 0);
    while (1) {
        sleep(1);
        printf("%s\n", tmp);
    }
    shmdt(tmp);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}

// gcc - o shareMemClient shareMemClient.c
// first run ./shareMemClient
// second run ./shareMemServer

// result:
// root@c36bc5a68254:~# ./shareMemClient
// key : -1

// a
// a
// a
// a
// ab
// ab
// ab
// ab
// abc
// abc
// abc
// abc
// abcd
// abcd
// abcd
// abcd
// abcde
// abcde
// abcde