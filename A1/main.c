// ASSIGNMENT 1 SYSC 4001 JAVERIA SOHAIL 101197163 //


#include <stdio.h>
#include <stdlib.h>

// Defining state constants 
enum state { NEW , READY, RUNNING, WAITING, TERMINATED };

// Establishing a struct for the process control block (PCB)
typedef struct {
    int pid;
    int arrival_time;
    int total_cpu_time;
    int io_frequency;
    int io_duration;
    int remaining_cpu_time;
    int state;
} PCB;

// Define a structure for tracking state transitions
typedef struct {
    int time;
    int pid;
    int old_state;
    int new_state;
} Transition;

// Function to read process data from a file and populate the PCB array
void readInputFile(PCB *pcbArray, int num_processes, FILE *file) {
    for (int i = 0; i < num_processes; i++) {
        fscanf(file, "%d %d %d %d %d", &pcbArray[i].pid, &pcbArray[i].arrival_time, 
               &pcbArray[i].total_cpu_time, &pcbArray[i].io_frequency, 
               &pcbArray[i].io_duration);
        pcbArray[i].remaining_cpu_time = pcbArray[i].total_cpu_time;
        pcbArray[i].state = NEW; // Initialize all processes to New state
    }
}

int main() {
    FILE *inputFile = fopen("test_case1.txt", "read");
    FILE *outputFile = fopen("test_case1_output.txt", "write");
    
    if (inputFile == NULL || outputFile == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    int num_processes;
    fscanf(inputFile, "%d", &num_processes);

    PCB *pcbArray = (PCB *)malloc(num_processes * sizeof(PCB)); // allocate the PCB memory size to the array for each process

    if (pcbArray == NULL) {
        printf("Memory allocation error.\n");
        return 1;
    }

    readInputFile(pcbArray, num_processes, inputFile);

    // Create lists for each process state
    PCB **state_lists = (PCB **)malloc(5 * sizeof(PCB *)); // we have 5 states
    for (int i = 0; i < 5; i++) {
        state_lists[i] = NULL;
    }

    // Create a list for tracking state transitions
    Transition *transitions = (Transition *)malloc(num_processes * sizeof(Transition)); // assign memory for transition of each state for each process
    int num_transitions = 0;

    int current_time = 0;
    int completed_processes = 0;

    while (completed_processes < num_processes) {
        // Check for processes that have arrived and are ready to run (given that they have all the resources)
        for (int i = 0; i < num_processes; i++) {
            if (pcbArray[i].arrival_time <= current_time && pcbArray[i].state == NEW) {
                pcbArray[i].state = READY;
                enqueue(&state_lists[READY], &pcbArray[i]); // Adding the process from New list to Ready list
                transitions[num_transitions++] = {current_time, pcbArray[i].pid, NEW, READY}; // Updating the transition of state with every increment
            }
        }

        // Simulate execution and I/O for processes
        for (int i = 0; i < num_processes; i++) {
            if (pcbArray[i].state == READY) {
                pcbArray[i].state = RUNNING;
                dequeue(&state_lists[READY]); // Remove from Ready list as now it is gone to Running state
                transitions[num_transitions++] = {current_time, pcbArray[i].pid, READY, RUNNING}; // Another transition has happened 
            } else if (pcbArray[i].state == RUNNING) {
                if (pcbArray[i].remaining_cpu_time > 0) {
                    pcbArray[i].remaining_cpu_time--;   //decrement the remaining CPU time as the clock has ticked once now

                    if (pcbArray[i].remaining_cpu_time == 0) {
                        pcbArray[i].state = TERMINATED; // end the process if there is no time left for the process
                        completed_processes++; 
                        transitions[num_transitions++] = {current_time, pcbArray[i].pid, RUNNING, TERMINATED};
                    } else if (current_time % pcbArray[i].io_frequency == 0) { // this checks if the io_freq is a multiple off the current time
                        pcbArray[i].state = WAITING; 
                        transitions[num_transitions++] = {current_time, pcbArray[i].pid, RUNNING, WAITING};
                    }
                }
            } else if (pcbArray[i].state == WAITING) {
                if (current_time % pcbArray[i].io_duration == 0) {
                    pcbArray[i].state = READY;
                    enqueue(&state_lists[READY], &pcbArray[i]); // Add back to Ready list
                    transitions[num_transitions++] = {current_time, pcbArray[i].pid, WAITING, READY};
                }
            }
        }

        current_time++; // increments the clock by 1 at every cycle
    }



     

