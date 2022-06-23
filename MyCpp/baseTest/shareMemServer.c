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
    int shmid = shmget(k, SIZE, 0);
    if (shmid < 0) {
        perror("shmget error\n");
        return 1;
    }
    char i = 'a';
    char* tmp = (char*)shmat(shmid, NULL, 0);
    for (; i <= 'z'; i++) {
        tmp[i - 'a'] = i;
        sleep(4);
    }
    shmdt(tmp);
    return 0;
}

// gcc - o shareMemServer shareMemServer.c

// first run ./shareMemClient
// second run ./shareMemServer