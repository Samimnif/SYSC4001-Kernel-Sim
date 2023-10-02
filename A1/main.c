/**
 * SYSC 4001 - Assignment 1
 *
 * @author Sami Mnif - 101199669
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

enum STATUS_ENUM
{
    NEW,
    READY,
    RUNNING,
    WAITING,
    TERMINATED
};

static const char *STATUS_STRING[] = {
    "NEW",
    "READY",
    "RUNNING",
    "WAITING",
    "TERMINATED"};

typedef struct Process
{
    int PID;
    int arrival_time;
    int CPU_time;
    int IO_frequency;
    int IO_duration;
} process;

typedef struct node
{
    process *p;
    struct node *next;
} node_t;

/**
 *
 */
process *create_process(int PID, int arrival_time, int CPU_time, int IO_frequency, int IO_duration)
{
    process *new_process = (process *)malloc(sizeof(process));
    new_process->PID = PID;
    new_process->arrival_time = arrival_time;
    new_process->CPU_time = CPU_time;
    new_process->IO_frequency = IO_frequency;
    new_process->IO_duration = IO_duration;
    return &new_process;
}

node_t *create_node(process *p)
{
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    new_node->p = p;
    new_node->next = NULL;

    return new_node;
}

node_t *add_node(node_t *n, node_t *head)
{
    if (head == NULL)
    {
        head = n;
    }
    else
    {
        node_t *current = head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = n;
    }
    return head;
}

bool remove_node(node_t *n, node_t *head)
{
    if (head == n)
    {
        head = head->next;
        n->next = NULL; // to isolate the node from the list
        return true;
    }
    else
    {
        node_t *current = head;
        node_t *prev = NULL;
        while (current->next != NULL)
        {
            if (current == n)
            {
                prev->next = current->next;
                n->next = NULL;
                return true;
            }
            prev = current;
            current = current->next;
        }
    }
    return false;
}


node_t fetch_data(FILE fp){
    
}

int main(int argc, char const *argv[])
{
    bool exit = false;
    int clock = 0;

    do
    {

    } while (!exit);
    return 0;
}
