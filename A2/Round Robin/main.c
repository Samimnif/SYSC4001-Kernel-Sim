/**
 * SYSC 4001 - Assignment 1
 *
 * @author Sami Mnif - 101199669
 * @author Javeria Sohail - 101197163
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

typedef struct Process
{
    int PID;
    int arrival_time;
    int CPU_time;
    int IO_frequency;
    int IO_frequency_left;
    int IO_duration;
    int IO_duration_left;
    int waiting_time; // for stats purposes only
    int end_time; // for stats purposes only
} process;

typedef struct node
{
    process *p;
    struct node *next;
} node_t;

/** create_process: takes in process details and create a preocess struct by adding it to the heap
 * by using malloc
 * Input Parameters:
 * PID, arrival_time, CPU_time, IO_frequency, IO_duration
 *
 * Output: a pointer to process
 */
process *create_process(int PID, int arrival_time, int CPU_time, int IO_frequency, int IO_duration)
{
    process *new_process = (process *)malloc(sizeof(process));
    new_process->PID = PID;
    new_process->arrival_time = arrival_time;
    new_process->CPU_time = CPU_time;
    new_process->IO_frequency = IO_frequency;
    new_process->IO_frequency_left = IO_frequency;
    new_process->IO_duration = IO_duration;
    new_process->IO_duration_left = IO_duration;
    new_process->waiting_time = 0;
    new_process->end_time = 0;
    return new_process;
}

/** create_node: creates a node (in the heap) to be used in a linked list. It takes a process and has a pointer to the next node.
 * Input Parameters: p (process)
 * Output: a pointer to the node
 */
node_t *create_node(process *p)
{
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    new_node->p = p;
    new_node->next = NULL;

    return new_node;
}

/** add_node: adds a node to the end of a specific linked list.
 * Inputs: n (pointer to the node), head (pointer to the head of the linked list).
 * Output: pointer to the head of the linked list
 *
 */
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

/** remove_node: removes a specific node from the linked list
 * Inputs: n (the node to be removed), head (the head of the linked list)
 * Output: a pointer to the head of the linked list (since the head could be removed)
 *
 */
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

/** getFirst_node: removes the first node of the linked list (the head) and returns a pointer to it.
 * Inputs: head (a pointer to the pointer of the head)
 * Output: a pointer to the first removed node
 *
 */
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

/** print_list: prints the linke dlist in more detail
 * Input: head (the head of the linked list)
 * Output: void (it wil print to the terminal the details)
 *
 */
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

/** print_listln: prints the linked list in one line
 * Input: head (the head of teh linked list)
 * Output: void (prints the linked list in one line)
 */
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

/** fetch_data: reads the file provided and extracts the details and saves it in to a linked
 * list that is made of nodes that contains the process structs
 * Input: filename (the name of the file conataining data)
 * Output: pointer to the head of newly created linked list
 *
 */
node_t *fetch_data(const char *filename)
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

/** write_process: takes details and appends it to an output file.
 * Inputs:
 * outputFile[](the ouptut file name), counter(the current clock), PID(the process PID),
 * old_state[](the previous state of the process), new_state[](the new state of the process)
 * Output: void (it writes to a output file)
 *
 */
void write_process(char outputFile[], int counter, int PID, const char old_state[], const char new_state[])
{
    FILE *output;
    output = fopen(outputFile, "a");
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
    const char *filename = argv[1];
    //char filename[] = "test_case_3.csv";
    char outputFile[] = "output-";
    printf("Input %s  **\n\n", filename);
    node_t *data = fetch_data(filename);
    
    //Creating an output filename depending on input filename
    strcat(outputFile, filename);
    //Accessing the ouput file and writing table headers
    FILE *output;
    output = fopen(outputFile, "a");
    fputs("Time of transition", output);
    fputs(",", output);
    fputs("PID", output);
    fputs(",", output);
    fputs("Old State", output);
    fputs(",", output);
    fputs("New State", output);
    fputs("\n", output);
    fclose(output);

    // Initialize the Queue/list for each state: READY, RUNNING, WAITING,TERMINATED
    node_t *readyList = NULL, *waitingList = NULL, *terminatedList = NULL, *running = NULL, *listHead, *tempNext; // Added some helper variables too
    //print_listln(data);

    bool exit = false;
    int clock = 0;

    printf("\nKERNEL SIM STARTS\n===================\n");
    while (!exit)
    {
        //This is just a Terminal Print Text for each clock cycle info
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

        // For stats only, increment waiting time if still in READY Queue
        listHead = readyList;
        while (listHead != NULL)
        {
            listHead->p->waiting_time++;
            listHead = listHead->next;
        }

        // IO List Check: to prepare the READY List before checking or assigning anything to the CPU
        listHead = waitingList;
        while (listHead != NULL)
        {
            /* Decrements every Item in the WAITING List as they access IO, and then check if their IO
               duration has ended, therfore will have to move it back to the READY Queue.               */
            listHead->p->IO_duration_left -= 1;
            if (listHead->p->IO_duration_left == 0)
            {
                tempNext = listHead->next;
                // Change of STATE here from WAITING to READY
                write_process(outputFile, clock, listHead->p->PID, "WAITING", "READY");
                //remove that specific node from WIATING list and add it at the end of the READY List
                waitingList = remove_node(listHead, waitingList);
                readyList = add_node(listHead, readyList);
                listHead = tempNext;
            }
            else
            {
                listHead = listHead->next;
            }
        }
        // Check for NEW arriving process to be added to READY Queue
        listHead = data;
        while (listHead != NULL)
        {
            if (listHead->p->arrival_time == clock)
            {
                tempNext = listHead->next;
                // Change of STATE here from NEW to READY
                write_process(outputFile, clock, listHead->p->PID, "NEW", "READY");
                data = remove_node(listHead, data);
                readyList = add_node(listHead, readyList);
                listHead = tempNext;
            }
            else
            {
                listHead = listHead->next;
            }
        }

        /* if the CPU is running then decrement the CPU Time and the IO Frequency and check if
           they need to change states.                                                          */
        if (running != NULL)
        {
            running->p->IO_frequency_left -= 1;
            running->p->CPU_time -= 1;
            if (running->p->CPU_time == 0)
            {
                // Process ended and changed to TERMINATED
                write_process(outputFile, clock, running->p->PID, "RUNNING", "TERMINATED");
                running->p->end_time = clock;
                terminatedList = add_node(running, terminatedList);
                running = NULL;
            }
            else if (running->p->IO_frequency_left == 0)
            {
                // Process needs IO access, status changed to WAITING
                write_process(outputFile, clock, running->p->PID, "RUNNING", "WAITING");
                running->p->IO_duration_left = running->p->IO_duration;
                waitingList = add_node(running, waitingList);
                running = NULL;
            }
            else{
                //In this part, if the CPU is already running and none of the above is met, then we terminate and move in READY list
                // Process met the Round Robin timeout
                write_process(outputFile, clock, running->p->PID, "RUNNING", "READY");
                readyList = add_node(running, readyList);
                running = NULL;
            }
            // If the process left CPU, get a new process from READY Queue immediately, else the CPU will be empty
            if (running == NULL)
            {
                if (readyList != NULL)
                {
                    running = add_node(getFirst_node(&readyList), running);
                    // Process moved to CPU. State changed from READY to RUNNING
                    write_process(outputFile, clock, running->p->PID, "READY", "RUNNING");
                    running->p->IO_frequency_left = running->p->IO_frequency;
                }
                else
                {
                    printf("READY QUEUE EMPTY\nCPU IDLE\n");
                }
            }
        }
        else // If the CPU is not Running, then get first Item from READY Queue
        {
            if (readyList != NULL)
            {
                running = add_node(getFirst_node(&readyList), running);
                // Process moved to CPU. State changed from READY to RUNNING
                write_process(outputFile, clock, running->p->PID, "READY", "RUNNING");
                running->p->IO_frequency_left = running->p->IO_frequency;
            }
            else
            {
                printf("READY QUEUE EMPTY\nCPU IDLE\n");
            }
        }
        // Check if the READY, WAITING, RUNNING, NEW list are empty --> Means all process are in TERMINATED list
        if (readyList == NULL && running == NULL && data == NULL && waitingList == NULL)
        {
            exit = true;
        }
        clock++;

    }

    printf("\n===================\nTERMINATED\n\nSTATS:\n");
    float average_waiting = 0, average_turnaround = 0, throuput_last = 0;
    int process_num = 0;
    listHead = terminatedList;
    //Going through all Process in the TERMINATED list and collect info like waiting time and number of process
    while (listHead != NULL)
    {
        printf("PID:%d      Waiting Time:%d     Turnaround:%d\n", listHead->p->PID, listHead->p->waiting_time, listHead->p->end_time - listHead->p->arrival_time);
        process_num++;
        average_waiting += listHead->p->waiting_time;
        average_turnaround += listHead->p->end_time - listHead->p->arrival_time;
        if (listHead->next == NULL){
            throuput_last = listHead->p->end_time;
        }
        listHead = listHead->next;
    }
    //Calculating Avergae Waiting Time and Printing it to thr Terminal
    printf("Average Waiting Time: %f\n", (average_waiting / process_num));
    printf("Average Turnaround Time: %f\n", (average_turnaround / process_num));
    printf("Average Throughput: %f\n", (float)(process_num / throuput_last));

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