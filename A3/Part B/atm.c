/**
 * ASSIGNMENT 3
 * @file atm.c
 * 
 * Description:
 * main atm service where it interacts with the user and the db_server.c
 * Receives inputs from usr and sends messages to db_server.c using message queues.
 * 
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

/** clearInputBuffer: clears input buffer
 * 
*/
void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

/** atm_user: the main atm code where it creates message queues and send messages nad receive with the db_server.c
 * Inputs: void
 * Outputs: void
 * 
*/
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
    char options[2];
    float withdraw_ammount;
    user_input.mesg_action = PIN;

    while (true)
    {
        printf("Please Enter your Account number (5 digit on the back of your card) or 'X' to exit\n");
        scanf("%s", user_input.account_no);
        
        // Checks for the number of digits in the account_no
        if (strlen(user_input.account_no) > 5)
        {
            printf("Account Number has to be 5 digits!!\n");
            //clearInputBuffer();
            continue;
        }
        // Checks if the user wants to exit
        if (user_input.account_no[0] == 'X')
        {
            printf("\nThank you for using our services\n");
            break;
        }
        printf("Please Enter the PIN code for Account#%s\n", user_input.account_no);
        //clearInputBuffer();
        scanf("%s", user_input.account_pin);
        // Checks for number of digits in the PIN
        if (strlen(user_input.account_pin) > 3 || strlen(user_input.account_pin) < 3)
        {
            //clearInputBuffer();
            printf("PIN numbers are 3 digits!!\n");
            continue;
        }
        message.account_d = user_input;
        message.account_d.mesg_action = PIN;
        //sends data to db_server.c
        msgsnd(msgid, &message, sizeof(message), 0);
        msgrcv(msgid, &message, sizeof(message), 1, 0);

        //Once data received, then checks the message action variable
        if (message.account_d.mesg_action == OK)
        {
            printf("PIN OK\n");
            //if the PIN ok then ask for options
            while (1)
            {
                printf("Please Select one of the options: (1) Show Balance  (2) Withdraw Money\n");
                //clearInputBuffer();
                //fgets(options, sizeof(options), stdin);
                scanf("%s", options);
                if (atoi(options) == 1)
                {
                    message.account_d.mesg_action = BALANCE;
                    msgsnd(msgid, &message, sizeof(message), 0);
                    msgrcv(msgid, &message, sizeof(message), 1, 0);
                    printf("Bank Statement:\n----\nAccount#: %s\nBalance: $%.2f\n", message.account_d.account_no, message.account_d.funds);
                    break;
                }
                else if ((atoi(options) == 2))
                {
                    printf("How much would you like to withdraw:\n");
                    scanf("%f", &withdraw_ammount);
                    message.account_d.mesg_action = WITHDRAW;
                    message.account_d.withdraw_q = withdraw_ammount;
                    msgsnd(msgid, &message, sizeof(message), 0);
                    msgrcv(msgid, &message, sizeof(message), 1, 0);
                    if (message.account_d.mesg_action == FUNDS_OK){
                        printf("Withdrawal completed successfully!\nNew Balance: $%.2f\n", message.account_d.funds);
                    }
                    else if (message.account_d.mesg_action == NSF)
                    {
                        printf("Not Enough Funds in your balance.\nPlease Try Later.\n");
                    }
                    break;
                }
                printf("You didn't select any of the presented options.\nPlease Try Again.\n");
            }
            break;
        }
        else if (message.account_d.mesg_action == PIN_WRONG)
        {
            // If the PIN is wrong, then Try again
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
        // parent atm
        atm_user();
    }
    else if (pid == 0)
    {
        // child db_sever.c
        printf("Child Started");

        execl("./db_server", "db_server", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }
    return 0;
}
