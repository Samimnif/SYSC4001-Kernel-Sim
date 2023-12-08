/**
 * ASSIGNMENT 3
 * db_editor.c
 * Description:
 * @author Sami Mnif - 101199669
 * @author Javeria Sohail - 101197163
 */
#include "data_struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdbool.h>

int main()
{
    key_t key;
    int msgid;
    mesg message;

    // ftok to generate unique key
    key = ftok("atm_key", 'M');

    if (key == -1)
    {
        perror("ftok");
        exit(0);
    }

    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1)
    {
        perror("msgget: msgget failed");
        exit(0);
    }
    account user_data;
    message.mesg_type = 1;
    message.account_d.mesg_action = UPDATE_DB;
    while (1)
    {
        printf("Please enter Account No:\n");
        scanf("%5s", user_data.account_no);
        printf("Please enter a PIN for Account#:\n");
        scanf("%4s", user_data.account_pin);
        printf("Please the funds for Account#:\n");
        scanf("%f", &user_data.funds);

        message.account_d = user_data;
        message.account_d.mesg_action = UPDATE_DB;
        msgsnd(msgid, &message, sizeof(message), 0);
    }
    // to destroy the message queue
    // msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
