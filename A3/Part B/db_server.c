/**
 * ASSIGNMENT 3
 * db_server.c
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

void update_db(info new_data)
{
    const char *filename = DB_FILE;
    const char *temp_filename = "temp_db_file.txt";

    FILE *fp, *temp_fp;
    fp = fopen(filename, "r");
    temp_fp = fopen(temp_filename, "w");
    fprintf(temp_fp, "Account,PIN,Funds\n");

    bool updated = false;
    char lineString[100], tempString[100];
    fgets(lineString, sizeof(lineString), fp); // Read and ignore the header line

    while (fgets(lineString, sizeof(lineString), fp))
    {
        strcpy(tempString, lineString);
        // Tokenize the line
        int account_no = atoi(strtok(lineString, ","));

        if (account_no == atoi(new_data.account_no))
        {
            // Update the line with new data
            fprintf(temp_fp, "%s,%s,%.2f\n", new_data.account_no, new_data.account_pin, new_data.funds_amount);
            updated = true;
        }
        else
        {
            // Copy the existing line to the temporary file
            fprintf(temp_fp, "%s", tempString);
        }
    }
    if (!updated)
    {
        fprintf(temp_fp, "%s,%d,%.2f\n", new_data.account_no, atoi(new_data.account_pin) - 1, new_data.funds_amount);
    }

    fclose(fp);
    fclose(temp_fp);

    // Rename the temporary file to the original file
    if (rename(temp_filename, filename) != 0)
    {
        perror("Error renaming file");
        exit(EXIT_FAILURE);
    }
}

bool check_pin(char *account, char *pin, info *user_data)
{
    const char *filename = DB_FILE;
    // char account_no[6], pin_no[4];
    // float funds_amount;
    FILE *fp;
    fp = fopen(filename, "r");
    char lineString[100];
    fgets(lineString, 100, fp);
    while (fgets(lineString, 100, fp))
    {
        // printf("%s", lineString);
        strcpy(user_data->account_no, strtok(lineString, ","));
        strcpy(user_data->account_pin, strtok(NULL, ","));
        user_data->funds_amount = (float)atof(strtok(NULL, ","));
        if (atoi(account) == atoi(user_data->account_no))
        {
            if ((atoi(pin) - 1) == atoi(user_data->account_pin))
            {
                fclose(fp);
                return true;
            }
            else
            {
                fclose(fp);
                return false;
            }
        }
    }
    fclose(fp);
    return false;
}

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
    // printf("DB: %d\n", key);

    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1)
    {
        perror("msgget: msgget failed");
        exit(0);
    }

    info user_data, temp;
    while (1)
    {
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
            break;

        case BALANCE:
            message.account_d.funds = user_data.funds_amount;
            msgsnd(msgid, &message, sizeof(message), 0);
            break;

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
            break;

        case UPDATE_DB:
            printf("Mesage Update Received\n");
            strcpy(temp.account_no, message.account_d.account_no);
            strcpy(temp.account_pin, message.account_d.account_pin);
            temp.funds_amount = message.account_d.funds;
            update_db(temp);
            message.account_d.mesg_action = IDLE;
            break;

        }
    }
    // to destroy the message queue
    // msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
