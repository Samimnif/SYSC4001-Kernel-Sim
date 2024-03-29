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
    key_t key = ftok("main.c", 'M');
    int msg_id = msgget(key, IPC_CREAT | 0666);

    if (msg_id == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Process 3 (Second Child)
    struct msg_buffer message;

    while (1) {
        // Receive the message from Process 2
        msgrcv(msg_id, &message, sizeof(message), 2, 0);

        // Process the message (add 1)
        message.data += 1;

        // Display the result
        printf("Process 3 received: %d\n", message.data);


    }
}

