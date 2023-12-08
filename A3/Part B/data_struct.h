#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#define DB_FILE "database.csv"

typedef enum action_type
{
    PIN,
    PIN_WRONG,
    OK,
    BALANCE,
    WITHDRAW,
    NSF,
    FUNDS_OK,
    UPDATE_DB,
    IDLE
} actions;

typedef struct account_data
{
    actions mesg_action;
    char account_no[6];
    char account_pin[4];
    float funds;
    float withdraw_q;
} account;

typedef struct mesg_buffer
{
    long mesg_type;
    account account_d;
} mesg;

typedef struct AccountInfo
{
    char account_no[6];
    char account_pin[4];
    float funds_amount;
} info;

#endif