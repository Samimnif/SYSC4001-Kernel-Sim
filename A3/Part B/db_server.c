/**
 * ASSIGNMENT 3
 * @file db_server.c
 *
 * Description:
 * db_server will run as a child of atm.c
 * Both will share the message queues and will actively communicate with each other.
 * db_server also communicates with db_editor to be able to edit the database file directly
 * through db_server.
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

/** update_db: update databse csv file with new data/ exisiting data
 * Depending on the account number, if it does exists, it will override it.
 * Else it will append the new account + its information to the bottom of the file.
 *
 * Input: new_data (info object with account info)
 * Output: void
 */
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

/** block_account: update databse csv file and blocks the specific account number
 * by changing the first digit of the account number by an X
 * Example:  X0117, 260, 1000.23
 *
 * Input: account (char for account number)
 * Output: void
 */
void block_account(char *account)
{
    const char *filename = DB_FILE;
    const char *temp_filename = "temp_db_file.txt";

    FILE *fp, *temp_fp;
    fp = fopen(filename, "r");
    temp_fp = fopen(temp_filename, "w");
    fprintf(temp_fp, "Account,PIN,Funds\n");

    char lineString[100], tempString[100];
    fgets(lineString, sizeof(lineString), fp); // Read and ignore the header line

    while (fgets(lineString, sizeof(lineString), fp))
    {
        strcpy(tempString, lineString);
        // Tokenize the line
        char *account_no_str = strtok(lineString, ",");
        int account_no = atoi(account_no_str);
        char pin[4];
        strcpy(pin, strtok(NULL, ","));
        float funds = (float)atof(strtok(NULL, ","));

        if (account_no == atoi(account))
        {
            account_no_str[0] = 'X';
            // Update the line with new data
            fprintf(temp_fp, "%s,%s,%.2f\n", account_no_str, pin, funds);
        }
        else
        {
            // Copy the existing line to the temporary file
            fprintf(temp_fp, "%s", tempString);
        }
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

/** check_pin: goes through the csv file database and checks
 * if the pin provided matches the PIN on the file.
 * If correct, the user data will be saved in the user_data info object.
 * Inputs: account number (char), pin number (char), full user data (info object)
 * Output: bool (true if it matches, false otherwise)
 */
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

/** add_attempt: adds an attempt to an account. If the account is not in history, then it gets added.
 * Otherwise, it increments the strikes.
 * Inputs: n (pointer to the node), head (pointer to the head of the linked list).
 * Output: pointer to the head of the linked list
 */
attempts *add_attempt(char *account, attempts *head)
{
    if (head == NULL)
    {
        attempts *new_attempt = (attempts *)malloc(sizeof(attempts));
        strcpy(new_attempt->account_no, account);
        new_attempt->strikes = 1;
        new_attempt->next = NULL;
        head = new_attempt;
    }
    else
    {
        attempts *current = head, *temp = head;
        while (current != NULL)
        {
            //printf("History: Account#%s, Strikes:%d\n", current->account_no, current->strikes);
            if (atoi(current->account_no) == atoi(account))
            {
                current->strikes++;
                if (current->strikes >= 3)
                {
                    block_account(current->account_no);
                    printf("Account#%s is Blocked\n", current->account_no);
                }
                return head;
            }
            temp = current;
            current = current->next;
        }
        attempts *new_attempt = (attempts *)malloc(sizeof(attempts));
        strcpy(new_attempt->account_no, account);
        new_attempt->strikes = 1;
        new_attempt->next = NULL;
        temp->next = new_attempt;
    }
    return head;
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

    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1)
    {
        perror("msgget: msgget failed");
        exit(0);
    }

    attempts *history = NULL;
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
                history = add_attempt(message.account_d.account_no, history);
                //printf("Updated history: %p\n", (void *)history);
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
            //printf("Mesage Update Received\n");
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
