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
    key_t key = ftok("main.c", 'M');
    int msg_id = msgget(key, IPC_CREAT | 0666);

    if (msg_id == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Process 2 forking
    pid_t pid1 = fork();

    // Process 1 (Parent)
    if (pid1 < 0) {
        perror("Error forking process 2");
        exit(EXIT_FAILURE);}

    if (pid1 == 0) {
        execl("./process2", "process2", NULL);
        exit(EXIT_FAILURE);}

    // Process 2 forking    
    pid_t pid2 = fork(); 

    if (pid2 < 0) {
        perror("Error forking process 3");
        exit(EXIT_FAILURE);}

    if (pid2 == 0) {
        execl("./process3", "process3", NULL);
        exit(EXIT_FAILURE);}

    // Process 1 (Parent)
    struct msg_buffer message;
    message.msg_type = 1;
    message.data = 1; 

    for (int i = 1; i < 10 ; ++i) {
        // Display the current number

        printf("Process 1 sending: %d\n", message.data);

        // Send the number to Process 2
        msgsnd(msg_id, &message, sizeof(message), 0);
        message.data+=1; 
        // Wait for child processes to finish
        usleep(50000);
    
    }
    // kill child processes
    kill(pid1, SIGTERM); 
    kill(pid2, SIGTERM); 
    // Remove the message queue
    msgctl(msg_id, IPC_RMID, NULL);
} 
    


