#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>

// Define the message structure
struct msg_buffer {
    long msg_type;
    int data;
};

int main() {
    key_t key = ftok("msg_key.txt", 'M');
    int msg_id = msgget(key, IPC_CREAT | 0666);
    if (msg_id == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    pid_t pid1, pid2;

    // Process 1 (Parent)
    if ((pid1 = fork()) == 0) {
        execl("./process2", "process2", NULL);
        perror("exec");
        exit(EXIT_FAILURE);
    } else {
        // Process 1 (Parent)
        struct msg_buffer message;
        message.msg_type = 1;

        for (int i = 1; i <= 5; ++i) {
            // Display the current number
            printf("Process 1 sending: %d\n", i);

            // Send the number to Process 2
            message.data = i;
            msgsnd(msg_id, &message, sizeof(message.data), 0);

            // Receive the processed number from Process 3
            msgrcv(msg_id, &message, sizeof(message.data), 3, 0);

            // Display the final result
            printf("Process 1 received: %d\n", message.data);
        }

        // Wait for child processes to finish
        wait(NULL);

        // Remove the message queue
        msgctl(msg_id, IPC_RMID, NULL);
    }

    return 0;
}
