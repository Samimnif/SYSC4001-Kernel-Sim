#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
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

void process1(char *shared_variable) {
    printf("I am Process 1\n");

    // create fork process
    pid_t pid = fork();

    if (pid < 0) {
        perror("error in creating fork process");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process (Process 2)
        execl("./process2_5", "process2_5", NULL);
        perror("exec problem");
    } else {
        // Parent process (Process 1)
        memory *shared_memory = (memory *)shmat(shm_id, NULL, 0);
        if (shared_memory == (memory *)-1) {
            perror("shmat");
            exit(EXIT_FAILURE);
        }

        printf("Process 1 waiting for Process 2...\n");
        while (1) {
            sem_wait(sem);

            printf("Select 1, 2, or x to display a message of the respective process...\n");

            char input[100];
            scanf("%99s", input);
            strncpy(shared_memory->inputval, input, sizeof(shared_memory->inputval));
            shared_memory->inputval[sizeof(shared_memory->inputval) - 1] = '\0';

            if (shared_memory->inputval[0] == '1') {
                printf("This is process 1\n");
            } else if (shared_memory->inputval[0] == 'x') {
                printf("Process 1 is quitting\n");
                kill(pid, SIGTERM);
                break;
            }

            sem_post(sem);
            sleep(1);
        }

        // Cleanup shared memory and semaphore
        shmdt(shared_memory);
        shmctl(shm_id, IPC_RMID, NULL);
        sem_destroy(sem);
        free(sem);
    }
}

int main() {
    key_t key = ftok("main_5.c", 'M');
    shm_id = shmget(key, sizeof(memory), IPC_CREAT | 0666);

    if (shm_id == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    sem = (sem_t *)malloc(sizeof(sem_t));
    sem_init(sem, 1, 1);

    process1(NULL);

    return 0;
}
