#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle_sigterm(int signum) {
    // Signal handler for SIGTERM (termination signal)
    printf("Received termination signal. Exiting Process 2.\n");
    exit(EXIT_SUCCESS);
}

void process2() {
    printf("I am Process 2\n");

    // Install a signal handler for SIGTERM
    signal(SIGTERM, handle_sigterm);

    while (1) {
        printf("Press '2' to display the message again or 'x' to exit: ");

        char input;
        scanf(" %c", &input);

        if (input == '2') {
            printf("I am Process 2\n");
        } else if (input == 'x') {
            // Send SIGTERM to itself
            kill(getpid(), SIGTERM);
        }
    }
}

int main() {
    process2();

    return 0;
}
