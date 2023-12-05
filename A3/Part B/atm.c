/**
 * ASSIGNMENT 3
 * atm.c
 * Description: 
 * @author Sami Mnif - 101199669
 * @author Javeria Sohail - 101197163
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdbool.h>

#include "data_struct.h"

void atm_user(){
    bool exit = false;
    account user_input;

    //while(!exit){
    printf("Please Enter your Account number (5 digit on the back of your card)");
    fgets(user_input.account_no, sizeof(user_input.account_no), stdin);
    printf("Accoutn:%s", user_input.account_no);
    //}
}

int main() {
    printf("\n$$========= ATM ==========$$\n");
    printf("WELCOME to the International ATM corporation\n");
    atm_user();

    return 0;
}
