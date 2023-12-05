#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

// Semaphore operations
struct sembuf acquire = {0, -1, SEM_UNDO};
struct sembuf release = {0, 1, SEM_UNDO};

void handle_sigterm(int signum) {
    // Signal handler for SIGTERM (termination signal)
    printf("Received termination signal. Exiting Process 2.\n");
    exit(EXIT_SUCCESS);
}

void process2(char *shared_variable) {
    printf("I am Process 2\n");

    // Install a signal handler for SIGTERM
    signal(SIGTERM, handle_sigterm);

    // Semaphore key
    key_t sem_key = ftok(".", 'S');
    int sem_id = semget(sem_key, 1, 0);
    if (sem_id == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Acquire the semaphore before accessing shared memory
        if (semop(sem_id, &acquire, 1) == -1) {
            perror("semop");
            exit(EXIT_FAILURE);
        }

        // Check the shared variable value and react accordingly
        char input = *shared_variable;
        if (input == '2') {
            printf("I am Process 2\n");
        } else if (input == 'x') {
            printf("Process 2 received exit signal. Exiting Process 2.\n");
            // Release the semaphore before exiting
            if (semop(sem_id, &release, 1) == -1) {
                perror("semop");
                exit(EXIT_FAILURE);
            }
            // Send SIGTERM to itself
            if (kill(getpid(), SIGTERM) == -1) {
                perror("kill");
                exit(EXIT_FAILURE);
            }
        }

        // Release the semaphore after accessing shared memory
        if (semop(sem_id, &release, 1) == -1) {
            perror("semop");
            exit(EXIT_FAILURE);
        }

        // Introduce a small delay to avoid busy waiting
        usleep(100000);  // 100 milliseconds
    }
}

int main() {
    key_t key = ftok(".", 'S');
    int shm_id = shmget(key, sizeof(char), IPC_CREAT | 0666);
    if (shm_id == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    char *shared_variable = (char *)shmat(shm_id, NULL, 0);
    if (shared_variable == (char *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    process2(shared_variable);

    // Cleanup shared memory
    shmdt(shared_variable);

    return 0;
}
