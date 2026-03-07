#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <stdatomic.h>

#define MSG_SIZE 256

typedef struct {
    atomic_int turn;
    char message[MSG_SIZE];
} SharedData;

int main() {
    SharedData *shm = mmap(NULL, sizeof(SharedData),
                           PROT_READ | PROT_WRITE,
                           MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    atomic_store(&shm->turn, 0);

    pid_t pid = fork();

    if (pid == 0) {
        while (atomic_load(&shm->turn) != 1)
            usleep(100);

        printf("Child received: %s\n", shm->message);

        strcpy(shm->message, "Hello from child!");
        atomic_store(&shm->turn, 2);

        _exit(0);
    }

    strcpy(shm->message, "Hello from parent!");
    atomic_store(&shm->turn, 1);

    while (atomic_load(&shm->turn) != 2)
        usleep(100);

    printf("Parent received: %s\n", shm->message);

    waitpid(pid, NULL, 0);
    munmap(shm, sizeof(SharedData));

    return 0;
}
