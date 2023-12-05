#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <signal.h>

#define SHM_SIZE  sizeof(char)

// Semaphore operations
struct sembuf acquire = {0, -1, SEM_UNDO};
struct sembuf release = {0, 1, SEM_UNDO};

volatile sig_atomic_t child_exit_flag = 0;
int sem_id;

void handle_sigchld(int signum) {
    // Signal handler for SIGCHLD (child process exit)
    child_exit_flag = 1;
}

void process1(char *shared_variable) {
    printf("I am Process 1\n");

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process (Process 2)
        execl("./process2", "process2", NULL);
        perror("exec");
        exit(EXIT_FAILURE);
    } else {
        // Parent process (Process 1)

        // Install a signal handler for SIGCHLD
        signal(SIGCHLD, handle_sigchld);

        // Wait for the child process to finish (Process 2)
        while (!child_exit_flag) {
            // Process 1 waits for Process 2
            printf("Process 1 waiting for Process 2...\n");
            sleep(1);
        }

        // Cleanup shared memory and semaphore
        shmdt(shared_variable);
        shmctl(shm_id, IPC_RMID, NULL);
        semctl(sem_id, 0, IPC_RMID);
    }
}

int main() {
    key_t key = ftok(".", 'S');
    int shm_id = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shm_id == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    char *shared_variable = (char *)shmat(shm_id, NULL, 0);
    if (shared_variable == (char *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Create a semaphore
    sem_id = semget(key, 1, IPC_CREAT | IPC_EXCL | 0666);
    if (sem_id == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    // Initialize the semaphore
    if (semctl(sem_id, 0, SETVAL, 1) == -1) {
        perror("semctl");
        exit(EXIT_FAILURE);
    }

    process1(shared_variable);

    return 0;
}
