/**
 * SYSC 4001 - Assignment 1
 *
 * Date: 28-09-2023
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
    "TERMINATED"
};

struct process
{
    int PID;
    int arrival_time;
    int CPU_time;
    int IO_frequency;
    int IO_duration;
};

struct task
{
    struct process *p;
    struct task *next;
};

/**
 * ß
*/
struct process* create_process(int PID, int arrival_time, int CPU_time, int IO_frequency, int IO_duration){
    struct process* new_process = (struct process*) malloc(sizeof(struct process));
    new_process->PID = PID;
    new_process->arrival_time = arrival_time;
    new_process->CPU_time = CPU_time;
    new_process->IO_frequency = IO_frequency;
    new_process->IO_duration = IO_duration;
    return &new_process;
}

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
