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
    int IO_Fclock;
    int IO_duration;
    int IO_Dleft;
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
    new_process->IO_Fclock = IO_frequency;
    new_process->IO_duration = IO_duration;
    new_process->IO_Dleft = IO_duration;
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

node_t *remove_node(node_t *n, node_t *head)
{
    if (head == n)
    {
        head = head->next;
        n->next = NULL; // to isolate the node from the list
    }
    else
    {
        node_t *current = head;
        node_t *prev = NULL;
        while (current != NULL)
        {
            if (current == n)
            {
                prev->next = current->next;
                n->next = NULL;
                return head;
            }
            prev = current;
            current = current->next;
        }
    }
    return head;
}

node_t *getFirst_node(node_t **head)
{
    node_t *temp;
    if (head != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        temp->next = NULL;
        return temp;
    }
    return NULL;
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

void write_process(char outputFile[], int counter, int PID, const char old_state[], const char new_state[]){
	FILE *output;
	output = fopen(outputFile , "a");
	char counter_char[1000];
	sprintf(counter_char, "%d", counter);
	char PID_char[1000];
	sprintf(PID_char, "%d", PID);
	fputs(counter_char, output);
	fputs(",", output);
	fputs(PID_char, output);
	fputs(",", output);
	fputs(old_state, output);
	fputs(",", output);
	fputs(new_state, output);
	fputs("\n", output);
	fclose(output);
}

int main(int argc, char const *argv[])
{
    // char *filename = argv[1];
    char filename[] = "test_case_1.csv";
    char outputFile[] = "output-";
    printf("\n Output: %s  **\n",outputFile);
	printf("Input %s  **\n",filename);
    node_t *data = fetch_data(filename);
    strcat(outputFile, filename);
    FILE *output;
	output = fopen(outputFile , "a");
	fputs("Time of transition", output);
	fputs(",", output);
	fputs("PID", output);
	fputs(",", output);
	fputs("Old State", output);
	fputs(",", output);
	fputs("New State", output);
	fputs("\n", output);
	fclose(output);

    node_t *newList = NULL, *readyList = NULL, *waitingList = NULL, *terminatedList = NULL, *running = NULL, *listHead, *tempNext;
    print_listln(data);

    bool exit = false;
    int clock = 0;

    do
    {
        printf("CLOCK %d\n", clock);
        printf("RUNNING: ");
        print_listln(running);
        printf("NEW List: ");
        print_listln(data);
        printf("READY List: ");
        print_listln(readyList);
        printf("IO List: ");
        print_listln(waitingList);
        printf("Terminaed List: ");
        print_listln(terminatedList);
        printf("\n");
        // IO List Check to prepare the READY List
        listHead = waitingList;
        while (listHead != NULL)
        {
            listHead->p->IO_Dleft -= 1;
            if (listHead->p->IO_Dleft == 0)
            {
                tempNext = listHead->next;
                // Change of STATE here from WAITING to READY
                write_process(outputFile, clock, listHead->p->PID, STATUS_STRING[listHead->p->status], STATUS_STRING[READY]);
                listHead->p->status = READY;
                waitingList = remove_node(listHead, waitingList);
                readyList = add_node(listHead, readyList);
                listHead = tempNext;
            }
            else
            {
                listHead = listHead->next;
            }
        }
        // NEW arriving Tasks to be adde to READY Queue
        listHead = data;
        while (listHead != NULL)
        {
            if (listHead->p->arrival_time == clock)
            {
                tempNext = listHead->next;
                // Chnage of STATE here from WAITING to READY
                write_process(outputFile, clock, listHead->p->PID, STATUS_STRING[listHead->p->status], STATUS_STRING[READY]);
                listHead->p->status = READY;
                data = remove_node(listHead, data);
                readyList = add_node(listHead, readyList);
                listHead = tempNext;
            }
            else
            {
                listHead = listHead->next;
            }
        }
        if (running != NULL)
        {
            running->p->IO_Fclock -= 1;
            running->p->CPU_time -= 1;
            if (running->p->CPU_time == 0)
            {
                // Process ended and changed to TERMINATED
                write_process(outputFile, clock, running->p->PID, STATUS_STRING[running->p->status], STATUS_STRING[TERMINATED]);
                running->p->status = TERMINATED;
                terminatedList = add_node(running, terminatedList);
                running = NULL;
            }
            else if (running->p->IO_Fclock == 0)
            {
                // Process needs IO access, status changed to WAITING
                write_process(outputFile, clock, running->p->PID, STATUS_STRING[running->p->status], STATUS_STRING[WAITING]);
                running->p->status = WAITING;
                running->p->IO_Dleft = running->p->IO_duration;
                waitingList = add_node(running, waitingList);
                running = NULL;
            }
        }
        else
        {
            if (readyList != NULL)
            {
                running = add_node(getFirst_node(&readyList), running);
                // Process moved to CPU. State changed from READY to RUNNING
                write_process(outputFile, clock, running->p->PID, STATUS_STRING[running->p->status], STATUS_STRING[RUNNING]);
                running->p->status = RUNNING;
                running->p->IO_Fclock = running->p->IO_frequency;
            }
            else
            {
                printf("READY QUEUE EMPTY\nCPU STALL\n");
            }
        }
        if (readyList == NULL && running == NULL && data == NULL && waitingList == NULL)
        {
            exit = true;
        }
        clock++;
        //sleep(1);

    } while (!exit);

    // Freeing the Heap
    while (terminatedList != NULL)
    {
        node_t *temp = terminatedList;
        terminatedList = terminatedList->next;
        free(temp->p);
        free(temp);
    }
    return 0;
}
