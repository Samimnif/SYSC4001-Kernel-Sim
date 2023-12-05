#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// Define the message structure
struct msg_buffer {
    long msg_type;
    int data;
};

int main() {
    key_t key = ftok(".", 'M');
    int msg_id = msgget(key, IPC_CREAT | 0666);
    if (msg_id == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Process 2 (First Child)
    struct msg_buffer message;

    while (1) {
        // Receive the message from Process 1
        msgrcv(msg_id, &message, sizeof(message.data), 1, 0);

        // Process the message (multiply by 2)
        message.data *= 2;

        // Display the result
        printf("Process 2 received: %d\n", message.data);

        // Send the result to Process 3
        message.msg_type = 2;
        msgsnd(msg_id, &message, sizeof(message), 0);
    }

    return 0;
}
