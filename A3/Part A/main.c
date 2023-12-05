#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

volatile sig_atomic_t child_exit_flag = 0;

void handle_sigchld(int signum) {
    // Signal handler for SIGCHLD (child process exit)
    child_exit_flag = 1;
}

void process1() {
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
    }
}

int main() {
    process1();

    return 0;
}
