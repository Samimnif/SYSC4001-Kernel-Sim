# SYSC4001-Kernel-Sim
## Authors
* Javeria Sohail - javeriasohail@cmail.carleton.ca
* Sami Mnif - samimnif@cmail.carleton.ca

<hr>

## Assignment 1
### Description
For this assignment, we created a FCFS Kernel Simulator. It reads data from csv file and outputs a file with the state change details for each process. The terminal will also print more detailed information of each process for each clock cycle. We also included waiting time stats at the end of the program.
### Usage
```bash
./test1.sh
./test2.sh
./test3.sh
```

In case you get a permission error for the bash files, please change
file permissions
```bash
chmod 755 {filename}
```

Once the script finished running, you will notice an output file has been created in this format
```
output-{input filename}
```

<hr>

## Assignment 2
### Description
* For this assignment we implemented multiple different Algorithms. First was FCFS, then FCFS with Priorities (no preemption) and then
Round Robin with **100ms** timeout.<br>
* We also have a Memory Management simulator where we used FCFS for processes and we implemented a main memory into the code where each arriving process needs to get allocated to main memory if there is space, and  if there isn't then the process waits until it gets freed.<br>
* The PCB did get changed and a memory requirement was added.
### Notes
* FCFS
  - There are two Test Cases from Part I: **PART1c.sh** and **PART1d.sh**
* Priorities
  - It is non preemptive, PCB is modified accordingly.
* Round Robin
  - The timeout is 100 ms, the same as the sim clock cycle.
* Memory Management
  - Scripts takes two files: 
    1. Test case PCB
    2. Memory partition size settings
  - The script will output two files:
    1. output-{case#}.csv --> simulation changes states
    2. outputMeme-{case#}.csv --> Current Memory information for every time a new process starts.
  - Test Cases from 1 - 4 are for **_testing_** purposes
  - Test Cases From 5 - 14 are for **_Analysis_** (found in Assignement PDF report)
  - These two memory settings set in the folder: 
    1. test_memory_1.csv --> From Assignment Instructions
    2. test_memory_2.csv --> From Assignment Instructions

-->GENERAL: Stats are saved in each Algorithm Folder in the README.md file.
### Usage
```bash
EXAMPLE:
./test1.sh
./test2.sh
./test3.sh
...
```

In case you get a permission error for the bash files, please change
file permissions
```bash
chmod 755 {filename}
```

Once the script finished running, you will notice an output file has been created in this format
```
output-{input filename}
```

<hr>

## Assignment 3
### Description
For this assignment, we created an ATM service.
The files are:
* **atm.c** - interacts with the user and db_server (acts as the bridge)
* **db_server.c** - mostly changes the database data, and receives messages from the db_editor and the atm.c
* **db_editor.c** - receives inputs from the user and sends it to db_server to add them to a database.
<br><br>
The atm_key is used to save the message token.<br>

### Assumptions
We assume that whoever is using the db_editor.c is a trained professional.
Meaning they know that they have to:
* Put exact 5 digits for the Account number. Anything more will not be accepted, and instead will take the first 5 digits of the input.
* Put 3 digits for account PIN. Anything more will not be accepted, and instead will take the first 3 digits of the input.
* Put any integer/float in the funds section.
<br>

We assume that whoever is using the db_server.c, is going to consider the following:
* Put exact 5 digits for the Account number. If they put more than 5, an error will be displayed. If less than 5 then the leading numbers will be filled with zeroes. For example, if the user enters 123, it will be considered as 00123.
* Put 3 digits for account PIN. If the user enters more or less than 3 digits, it will give an error and return to step 1 (Asking Account number).
* Select one of the two options: 1 for Balance display or 2 for the withdraw function.

### Best Practices
* You will notice there is a data_struct.h file that contains all the defined structs, that are used across all three files.
* We included all the necessary comments and assumptions in this README and in the code file description (top of the file).

### Usage
**IMPORTANT INFO:** Once you finish one transaction in the atm, the process will end and exit. This will cause unsyncing of the db_editor. So to resync, restart the db_editor after you start the atm process again.<br>

Make sure you compile all three files: atm.c, db_server.c and db_editor.c <br>
You have to first open two terminal windows
Then run the atm service in the first terminal.
```bash
./atm 
```
Then run the db_editor in the second terminal
```bash
./db_editor
```

In case you get a permission error for the bash files, please change
file permissions
```bash
chmod 777 {filename}
```

<hr>

# Copyright
Copyright© 2023
