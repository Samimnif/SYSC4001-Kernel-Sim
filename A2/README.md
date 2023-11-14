# Assignement 2
## Authors
* Javeria Sohail - ID: **101197163** - javeriasohail@cmail.carleton.ca
* Sami Mnif - ID: **101199669** - samimnif@cmail.carleton.ca
## Details
* For this assignement we implemented multiple different Algorithms. First was FCFS, then FCFS with Priorities (no preemption) and then
Round Robin with **100ms** timeout.<br>
* We also have a Memory Managment simulator where we used FCFS for processes and we implemented a main memory into the code where each arriving process needs to get allocated to main memory if there is space, and  if there isn't then the process waits until it gets freed.<br>
* The PCB did get changed and a memory requirement was added.
## Notes
* FCFS
  - There are two Test Cases from Part I: **PART1c.sh** and **PART1d.sh**
* Priorities
  - It is non preemptive, PCB is modified accordingly.
* Round Robin
  - The timeout is 100 ms, same as the sim clock cycle.
* Memory Management
  - The scripts takes two files: 
    1. Test case PCB
    2. Memory partition sizes settings
  - The script will output two files:
    1. output-{case#}.csv --> simulation changes states
    2. outputMeme-{case#}.csv --> Current Memory information for every time a new process starts.
  - Test Cases from 1 - 4 are for **_testing_** purposes
  - Test Cases From 5 - 14 are for **_Analysis_** (found in Assignement PDF report)
  - There two memory settings set in the folder: 
    1. test_memory_1.csv --> From Assignment Instructions
    2. test_memory_2.csv --> From Assignment Instructions

-->GENERAL: Stats are saved in each Algorith Folder in teh README.md file. Analysis of the stats are in the Assignment Report.
## Usage
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

Once the script finished running, you will notice an output file has bee created in this format
```
output-{input filename}
```