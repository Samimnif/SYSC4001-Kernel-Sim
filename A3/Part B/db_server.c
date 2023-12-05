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

#include "data_struct.h"

int main()
{
    key_t key2;
    int msgid;
    mesg message_received;

    // ftok to generate unique key
    key2 = ftok("atm_key", 65);

    if (key2 == -1)
    {
        perror("ftok");
        exit(0);
    }
    printf("DB: %d", key2);

    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key2, 0666 | IPC_CREAT);
    if (msgid == -1)
    {
        perror("msgget: msgget failed");
        exit(0);
    }

    while (1)
    {
        // msgrcv to receive message
        msgrcv(msgid, &message_received, sizeof(message_received), 0, 0);

        printf("Account number : %s \n", message_received.account_d.account_no);
    }
    // to destroy the message queue
    // msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
