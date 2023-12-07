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

typedef struct AccountInfo
{
    char account_no[6];
    char account_pin[4];
    float funds_amount;
} info;

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

    info user_data;
    while (1)
    {
        printf("Please enter Account No:\n");
        scanf("%f", &user_data.account_no);
        printf("Please enter a PIN for Account#:\n");
        scanf("%f", &user_data.account_pin);
        printf("Please the funds for Account#:\n");
        scanf("%f", &user_data.funds_amount);

        msgsnd(msgid, &message, sizeof(message), 0);
        // msgrcv to receive message
        msgrcv(msgid, &message, sizeof(message), 0, 0);

        // printf("Account number received: %s \n", message.account_d.account_no);
        switch (message.account_d.mesg_action)
        {
        case PIN:
            if (check_pin(message.account_d.account_no, message.account_d.account_pin, &user_data))
            {
                message.account_d.mesg_action = OK;
                msgsnd(msgid, &message, sizeof(message), 0);
            }
            else
            {
                message.account_d.mesg_action = PIN_WRONG;
                msgsnd(msgid, &message, sizeof(message), 0);
            }
            continue;
        case BALANCE:
            message.account_d.funds = user_data.funds_amount;
            msgsnd(msgid, &message, sizeof(message), 0);

        case WITHDRAW:
            if (message.account_d.withdraw_q > user_data.funds_amount)
            {
                message.account_d.mesg_action = NSF;
            }
            else
            {
                user_data.funds_amount -= message.account_d.withdraw_q;
                message.account_d.funds = user_data.funds_amount;
                update_db(user_data);
                message.account_d.mesg_action = FUNDS_OK;
            }
            msgsnd(msgid, &message, sizeof(message), 0);

        case UPDATE_DB:
        /*
        default:
            printf("Went to default:\n");*/
        }
    }
    // to destroy the message queue
    // msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
