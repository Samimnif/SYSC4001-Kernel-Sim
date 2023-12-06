/**
 * ASSIGNMENT 3
 * atm.c
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

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void atm_user()
{
    key_t key;
    int msgid;
    mesg message;

    // ftok to generate unique key
    key = ftok("atm_key", 'M');
    if (key == -1)
    {
        perror("ftok");
        exit(EXIT_FAILURE);
    }
    //printf("ATM: %d\n", key);

    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1)
    {
        perror("msgget: msgget failed");
        exit(0);
    }
    message.mesg_type = 1;

    printf("\n$$========= ATM ==========$$\n");
    printf("WELCOME to the International ATM corporation\n");
    bool exit = false;
    account user_input;
    user_input.mesg_action = PIN;

    while (true)
    {
        printf("Please Enter your Account number (5 digit on the back of your card)\n");
        fgets(user_input.account_no, sizeof(user_input.account_no), stdin);
        if (strlen(user_input.account_no) > 6)
        {
            continue;
        }
        if (user_input.account_no[0] == 'X'){
            printf("Thank you for using our services");
            break;
        }
        printf("Please Enter the PIN code for Account#%s\n", user_input.account_no);
        clearInputBuffer();
        fgets(user_input.account_pin, sizeof(user_input.account_pin), stdin);
        if (strlen(user_input.account_pin) > 4)
        {
            continue;
        }
        message.account_d = user_input;
        message.account_d.mesg_action = PIN;
        msgsnd(msgid, &message, sizeof(message), 0);
        msgrcv(msgid, &message, sizeof(message), 1, 0);
        printf("Message feedback\n");
        clearInputBuffer();
        if (message.account_d.mesg_action == OK)
        {
            printf("PIN OK\n");
            break;
        }
        else if (message.account_d.mesg_action == PIN_WRONG)
        {
            printf("Wrong PIN\n");
            continue;
        }
    }
    msgctl(msgid, IPC_RMID, NULL);
}

int main()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid > 0)
    {
        //parent
        atm_user();
    }
    else if (pid == 0)
    {
        printf("Child Started");
        
        execl("./db_server", "db_server", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }
    return 0;
}
