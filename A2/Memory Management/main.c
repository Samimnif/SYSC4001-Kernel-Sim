/**
 * SYSC 4001 - Assignment 2
 * Memory Management
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
    int memory_needed;
    int waiting_time; // for stats purposes only
    int end_time; // for stats purposes only
    int partition_size; //Main Memory Partition Used
} process;

typedef struct Memory
{
    process *p;
    int position_num; // not too relevent, but might use it later
    int size;
    int hole;
} memory_part;

typedef struct node
{
    process *proc;
    memory_part *mem_part;
    struct node *next;
} node_t;

/** create_process: takes in process details and create a preocess struct by adding it to the heap
 * by using malloc
 * Input Parameters:
 * PID, arrival_time, CPU_time, IO_frequency, IO_duration, memory_needed
 *
 * Output: a pointer to process
 */
process *create_process(int PID, int arrival_time, int CPU_time, int IO_frequency, int IO_duration, int memory_needed)
{
    process *new_process = (process *)malloc(sizeof(process));
    new_process->PID = PID;
    new_process->arrival_time = arrival_time;
    new_process->CPU_time = CPU_time;
    new_process->IO_frequency = IO_frequency;
    new_process->IO_frequency_left = IO_frequency;
    new_process->IO_duration = IO_duration;
    new_process->IO_duration_left = IO_duration;
    new_process->memory_needed = memory_needed;
    new_process->waiting_time = 0;
    return new_process;
}

/** create_memory_part: takes in memory partition info and creates a new partition
 *
 */
memory_part *create_memory_part(process *p, int num, int size, int hole)
{
    memory_part *new_mempart = (memory_part *)malloc(sizeof(memory_part));
    new_mempart->p = p;
    new_mempart->position_num = num;
    new_mempart->size = size;
    new_mempart->hole = size;
    return new_mempart;
}

/** create_node: creates a node (in the heap) to be used in a linked list. It takes a process and has a pointer to the next node.
 * Input Parameters: p (process)
 * Output: a pointer to the node
 */
node_t *create_node(process *process, memory_part *partition)
{
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    if (process != NULL && partition == NULL)
    {
        new_node->proc = process;
        new_node->mem_part = NULL; // To define the node as a Process or Memory Node
    }
    else
    {
        new_node->mem_part = partition;
        new_node->proc = NULL; // To define the node as a Process or Memory Node
    }
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

/**
 *
 */
bool allocate_memory(process *p, node_t *head)
{
    node_t *current = head;
    while (current != NULL)
    {
        if (current->mem_part->size >= p->memory_needed && current->mem_part->p == NULL)
        {
            current->mem_part->p = p;
            current->mem_part->hole = current->mem_part->size - p->memory_needed;
            p->partition_size = current->mem_part->size;
            return true;
        }
        current = current->next;
    }
    return false;
}

/**
 *
 */
bool deallocate_memory(process *p, node_t *head)
{
    node_t *current = head;
    while (current != NULL)
    {
        if (current->mem_part->p == p)
        {
            current->mem_part->p = NULL;
            current->mem_part->hole = current->mem_part->size;
            return true;
        }
        current = current->next;
    }
    return false;
}

int total_mem_used(node_t *head)
{
    node_t *current = head;
    int sum = 0;
    while (current != NULL)
    {
        if (current->mem_part->p != NULL)
        {
            sum += current->mem_part->p->memory_needed;
        }
        current = current->next;
    }
    return sum;
}

int partitions_free (node_t *head)
{
    node_t *current = head;
    int sum = 0;
    while (current != NULL)
    {
        if (current->mem_part->p == NULL)
        {
            sum++;
        }
        current = current->next;
    }
    return sum;
}

int total_mem_free (node_t *head)
{
    node_t *current = head;
    int sum = 0;
    while (current != NULL)
    {
        if (current->mem_part->p != NULL)
        {
            sum += current->mem_part->hole;
        }
        current = current->next;
    }
    return sum;
}

int total_usable_mem (node_t *head)
{
    node_t *current = head;
    int sum = 0;
    while (current != NULL)
    {
        if (current->mem_part->p == NULL)
        {
            sum += current->mem_part->size;
        }
        current = current->next;
    }
    return sum;
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
        p = current->proc;
        printf("PID: %d\n", p->PID);
        printf("Memory Needed: %d\n", p->memory_needed);
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
        p = current->proc;
        printf("%d --> ", p->PID);
        current = current->next;
    }
    printf("NULL\n");
}

/**
 *
 */
void print_memory(node_t *head)
{
    node_t *current = head;
    int PID = 0, mem_needed = 0;
    memory_part *mem_part;
    while (current != NULL)
    {
        mem_part = current->mem_part;
        if (mem_part->p != NULL)
        {
            PID = mem_part->p->PID;
            mem_needed = mem_part->p->memory_needed;
        }
        printf("-----------------------\n");
        printf("%d: SIZE: %dK   |  PID:%d -%dK  |  Hole Left: %dK\n", mem_part->position_num, mem_part->size, PID, mem_needed, mem_part->hole);
        current = current->next;
        PID = 0; // to reset the print PID - used only for display
        mem_needed = 0;
    }
    printf("-----------------------\n");
}

/** fetch_data: reads the file provided and extracts the details and saves it in to a linked
 * list that is made of nodes that contains the process structs
 * Input: filename (the name of the file conataining data)
 * Output: pointer to the head of newly created linked list
 *
 */
node_t *fetch_data(const char *filename)
{
    int pid, arrival_time, CPU_time, IO_frequency, IO_duration, Memory_needed;
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
        Memory_needed = atoi(strtok(NULL, ","));
        process *p = create_process(pid, arrival_time, CPU_time, IO_frequency, IO_duration, Memory_needed);
        node_t *n = create_node(p, NULL);
        data = add_node(n, data);
    }
    printf("\nChecking Data:\n");
    print_list(data);
    print_listln(data);
    fclose(fp);
    return data;
}

/**
 *
 */
node_t *fetch_memory_settings(const char *filename)
{
    int part_num, part_size;
    node_t *data = NULL;
    FILE *fp;
    fp = fopen(filename, "r");
    char lineString[100];
    fgets(lineString, 100, fp);
    while (fgets(lineString, 100, fp))
    {
        printf("%s", lineString);
        part_num = atoi(strtok(lineString, ","));
        part_size = atoi(strtok(NULL, ","));
        memory_part *new_part = create_memory_part(NULL, part_num, part_size, 0);
        node_t *n = create_node(NULL, new_part);
        data = add_node(n, data);
    }
    printf("\nChecking Memory Settings:\n");
    print_memory(data);
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

/**
 * 
*/
void write_memory(char outputFile[], int counter, int PID, int memory_used, int partitions_used, int free_memory, int usable_memory)
{
    FILE *output;
    output = fopen(outputFile, "a");
    char counter_char[1000], memory_used_char[1000], partitions_used_char[1000], free_memory_char[1000], usable_memory_char[1000];
    sprintf(counter_char, "%d", counter);
    char PID_char[1000];
    sprintf(PID_char, "%d", PID);
    fputs(counter_char, output);
    fputs(",", output);
    fputs(PID_char, output);
    fputs(",", output);
    sprintf(memory_used_char, "%d", memory_used);
    fputs(memory_used_char, output);
    fputs(",", output);
    sprintf(partitions_used_char, "%d", partitions_used);
    fputs(partitions_used_char, output);
    fputs(",", output);
    sprintf(free_memory_char, "%d", free_memory);
    fputs(free_memory_char, output);
    fputs(",", output);
    sprintf(usable_memory_char, "%d", usable_memory);
    fputs(usable_memory_char, output);
    fputs("\n", output);
    fclose(output);
}

int main(int argc, char const *argv[])
{
    const char *filename = argv[1];
    const char *settingsFile = argv[2];
    // char filename[] = "test_case_3.csv";
    
    char outputFile[100];
    char outputMemeFile[100];
    printf("Input %s  **\n\n", filename);
    node_t *data = fetch_data(filename);
    node_t *main_memory = fetch_memory_settings(settingsFile);

    // Creating an output filename depending on input filename
    strcpy(outputFile, "output-");
    strcpy(outputMemeFile, "outputMeme-");
    strcat(outputFile, filename);
    strcat(outputMemeFile, filename);
    // Accessing the ouput file and writing table headers
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

    output = fopen(outputMemeFile, "a");
    fputs("Time of transition", output);
    fputs(",", output);
    fputs("PID", output);
    fputs(",", output);
    fputs("Memory Used", output);
    fputs(",", output);
    fputs("Partition Free", output);
    fputs(",", output);
    fputs("Total Free Memory", output);
    fputs(",", output);
    fputs("Total Usable Memory", output);
    fputs("\n", output);
    fclose(output);

    // Initialize the Queue/list for each state: READY, RUNNING, WAITING,TERMINATED
    node_t *readyList = NULL, *waitingList = NULL, *terminatedList = NULL, *running = NULL, *listHead, *tempNext; // Added some helper variables too
    // print_listln(data);

    bool exit = false;
    int clock = 0;

    printf("\nKERNEL SIM STARTS\n===================\n");
    while (!exit)
    {
        // This is just a Terminal Print Text for each clock cycle info
        printf("CLOCK %d\n", clock);
        printf("MAIN MEMORY:\n");
        print_memory(main_memory);
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
            listHead->proc->waiting_time++;
            listHead = listHead->next;
        }

        // IO List Check: to prepare the READY List before checking or assigning anything to the CPU
        listHead = waitingList;
        while (listHead != NULL)
        {
            /* Decrements every Item in the WAITING List as they access IO, and then check if their IO
               duration has ended, therfore will have to move it back to the READY Queue.               */
            listHead->proc->IO_duration_left -= 1;
            if (listHead->proc->IO_duration_left == 0)
            {
                tempNext = listHead->next;
                // Change of STATE here from WAITING to READY
                write_process(outputFile, clock, listHead->proc->PID, "WAITING", "READY");
                // remove that specific node from WIATING list and add it at the end of the READY List
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
            if (listHead->proc->arrival_time <= clock)
            {
                tempNext = listHead->next;
                // Change of STATE here from NEW to READY
                if (allocate_memory(listHead->proc, main_memory))
                {
                    write_process(outputFile, clock, listHead->proc->PID, "NEW", "READY");
                    write_memory(outputMemeFile, clock, listHead->proc->PID, total_mem_used(main_memory), partitions_free(main_memory), total_mem_free(main_memory), total_usable_mem(main_memory));
                    data = remove_node(listHead, data);
                    readyList = add_node(listHead, readyList);
                    listHead = tempNext;
                }
                else
                {
                    printf("NO FREE MEMORY");
                    listHead = listHead->next;
                }
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
            running->proc->IO_frequency_left -= 1;
            running->proc->CPU_time -= 1;
            if (running->proc->CPU_time == 0)
            {
                // Process ended and changed to TERMINATED
                deallocate_memory(running->proc, main_memory);
                write_process(outputFile, clock, running->proc->PID, "RUNNING", "TERMINATED");
                running->proc->end_time = clock;
                terminatedList = add_node(running, terminatedList);
                running = NULL;
            }
            else if (running->proc->IO_frequency_left == 0)
            {
                // Process needs IO access, status changed to WAITING
                write_process(outputFile, clock, running->proc->PID, "RUNNING", "WAITING");
                running->proc->IO_duration_left = running->proc->IO_duration;
                waitingList = add_node(running, waitingList);
                running = NULL;
            }
            // If the process left CPU, get a new process from READY Queue immediately, else the CPU will be empty
            if (running == NULL)
            {
                if (readyList != NULL)
                {
                    running = add_node(getFirst_node(&readyList), running);
                    // Process moved to CPU. State changed from READY to RUNNING
                    write_process(outputFile, clock, running->proc->PID, "READY", "RUNNING");
                    running->proc->IO_frequency_left = running->proc->IO_frequency;
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
                write_process(outputFile, clock, running->proc->PID, "READY", "RUNNING");
                running->proc->IO_frequency_left = running->proc->IO_frequency;
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
        printf("PID:%d      Waiting Time:%d     Turnaround:%d\n", listHead->proc->PID, listHead->proc->waiting_time, listHead->proc->end_time - listHead->proc->arrival_time);
        process_num++;
        average_waiting += listHead->proc->waiting_time;
        average_turnaround += listHead->proc->end_time - listHead->proc->arrival_time;
        if (listHead->next == NULL){
            throuput_last = listHead->proc->end_time;
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
        free(temp->proc);
        free(temp);
    }
    return 0;
}