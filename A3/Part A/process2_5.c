#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <semaphore.h>
#include <string.h>

#define SHM_SIZE sizeof(char)

typedef struct {
    char inputval[100];
} memory;

sem_t *sem;
int shm_id;

int main() {
    key_t key = ftok("main_5.c", 'M');
    shm_id = shmget(key, sizeof(memory), 0666);
    if (shm_id == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    memory *shared_memory = (memory *)shmat(shm_id, NULL, 0);
    if (shared_memory == (memory *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    sem = (sem_t *)malloc(sizeof(sem_t));
    sem_init(sem, 1, 1);

    while (1) {
        sem_wait(sem);

        // Check the value of the shared variable
        if (shared_memory->inputval[0] == '1') {
            printf("Process 2: Received 1\n");
        } else if (shared_memory->inputval[0] == '2') {
            printf("Process 2: Received 2\n");
        } else if (shared_memory->inputval[0] == 'x') {
            printf("Process 2: Received x\n");
            break;  // Exit the loop on 'x'
        }

        // Release the semaphore
        sem_post(sem);

        // Add some delay to avoid busy-waiting
        sleep(1);
    }

    // Detach from shared memory
    shmdt(shared_memory);

    // Cleanup semaphore
    sem_destroy(sem);
    free(sem);

    return 0;
}
