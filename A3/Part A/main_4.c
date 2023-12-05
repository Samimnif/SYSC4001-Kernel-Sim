#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>

#define SHM_SIZE  sizeof(char)

volatile sig_atomic_t child_exit_flag = 0;

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

        // Cleanup shared memory
        shmdt(shared_variable);
        shmctl(shm_id, IPC_RMID, NULL);
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

    process1(shared_variable);

    return 0;
}
