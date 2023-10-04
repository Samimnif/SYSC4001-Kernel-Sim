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

enum P_STATUS
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
    enum P_STATUS status;
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
    new_process->status = NEW;
    return new_process;
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

void print_list(node_t *head)
{
    node_t *current = head;
    process *p;
    while (current != NULL)
    {
        p = current->p;
        printf("PID: %d\n", p->PID);
        printf("Arival Time: %d\n", p->arrival_time);
        printf("CPU Time: %d\n", p->CPU_time);
        printf("IO Frequency: %d\n", p->IO_frequency);
        printf("IO Duration: %d\n", p->IO_duration);
        printf("-----------------------\n");
        current = current->next;
    }
}

void print_listln(node_t *head)
{
    node_t *current = head;
    process *p;
    while (current != NULL)
    {
        p = current->p;
        printf("%d --> ", p->PID);
        current = current->next;
    }
    printf("NULL\n");
}

node_t *fetch_data(char *filename)
{
    int pid, arrival_time, CPU_time, IO_frequency, IO_duration;
    node_t *data = NULL;
    FILE *fp;
    fp = fopen(filename, "r");
    char lineString[100];
    fgets(lineString, 100, fp);
    while (fgets(lineString, 100, fp))
    {
        printf("%s", lineString);
        pid = atoi(strtok(lineString, ","));
        arrival_time = atoi(strtok(NULL, ","));
        CPU_time = atoi(strtok(NULL, ","));
        IO_frequency = atoi(strtok(NULL, ","));
        IO_duration = atoi(strtok(NULL, ","));
        process *p = create_process(pid, arrival_time, CPU_time, IO_frequency, IO_duration);
        node_t *n = create_node(p);
        data = add_node(n, data);
    }
    printf("\nChecking Data:\n");
    print_list(data);
    print_listln(data);
    fclose(fp);
    return data;
}

int main(int argc, char const *argv[])
{
    //char *filename = argv[1];
    char filename[] = "test_case_1.csv";
    node_t* data = fetch_data(filename);

    bool exit = false;
    int clock = 0;

    do
    {

    } while (!exit);

    //Freeing the Heap
    while (data!= NULL){
        node_t *temp = data;
        data = data->next;
        free(temp->p);
        free(temp);
    }
    return 0;
}
