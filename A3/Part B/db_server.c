/**
 * ASSIGNMENT 3
 * db_server.c
 * Description: 
 * @author Sami Mnif - 101199669
 * @author Javeria Sohail - 101197163
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "data_struct.h"

int main() {
    printf("I am on");
    key_t key; 
    int msgid;
    mesg message_received;
  
    // ftok to generate unique key 
    key = ftok("atm_key", 65); 
  
    // msgget creates a message queue 
    // and returns identifier 
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1){
        perror("msgget: msgget failed");
        exit(0);
    }
  
    // msgrcv to receive message 
    msgrcv(msgid, &message_received, sizeof(message_received), 1, 0); 
    ssize_t bytes_received = msgrcv(msgid, &message_received, sizeof(message_received), 1, 0);
    // Check for errors in receiving the message
    if (bytes_received == -1) {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }

    printf("Account number : %s \n", message_received.account_d.account_no); 
  
    // to destroy the message queue 
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
