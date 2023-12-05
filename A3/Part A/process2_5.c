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
        printf("Press '2' to display the message again or 'x' to exit: ");

        char input;
        scanf(" %c", &input);

        // Acquire the semaphore before accessing shared memory
        if (semop(sem_id, &acquire, 1) == -1) {
            perror("semop");
            exit(EXIT_FAILURE);
        }

        // Store the input value in the shared variable
        *shared_variable = input;

        // Release the semaphore after accessing shared memory
        if (semop(sem_id, &release, 1) == -1) {
            perror("semop");
            exit(EXIT_FAILURE);
        }

        if (input == '2') {
            printf("I am Process 2\n");
        } else if (input == 'x') {
            // Send SIGTERM to itself
            if (kill(getpid(), SIGTERM) == -1) {
                perror("kill");
                exit(EXIT_FAILURE);
            }
        }
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
