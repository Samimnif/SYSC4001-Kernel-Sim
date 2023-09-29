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


struct process {
    int PID;
    int arrival_time;
    int CPU_time;
    int IO_frequency;
    int IO_duration;

};

struct task{
    struct process* p;
    struct task* next;
};



int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
