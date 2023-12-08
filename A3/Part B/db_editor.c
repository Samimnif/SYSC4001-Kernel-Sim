/**
 * ASSIGNMENT 3
 * @file db_editor.c
 * Description:
 * db_editor runs seperatly in a second terminal window.
 * Mainly used for updating and adding new Accounts to the databse file.
 * Once it receives all the inputs required from the user, sends a message to the db_server.c
 * 
 * **IMPORTANT INFO:** Once you finish one transaction in the atm, the atm process will end and exit. 
 * This will cause unsyncing of the db_editor. So to resync the editor, restrat the db_editor afer you start the atm process again.
 * 
 * We assume that whoever is using the db_editor.c is a trained professional.
 * Meaning they know that they have to:
 *   * Put exact 5 digits for the Account number. Anything more will not be accepted, and instead will take the frst 5 digits of the input.
 *   * Put 3 digits for account PIN. Anything more will not be accepted, and instead will take the frst 3 digits of the input.
 *   * Put any integer/float in he funds section.
 * 
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
