# Assignement 2
## Details
For this assignement we created a FCFS Kernel Simulator. It reads data from csv file and ouputs a file with the states changes details for each process. The terminal will also print more detailed information of each process for each clock cycle. We also included a waiting time stats at the end of the program.
### Results
* Test Case 1
```text
STATS:
PID:1001      Waiting Time:0     Turnaround:100
PID:1002      Waiting Time:0     Turnaround:200
PID:1003      Waiting Time:0     Turnaround:110
PID:1004      Waiting Time:10    Turnaround:120
Average Waiting Time: 2.500000
Average Turnaround Time: 132.500000
Average Throughput: 0.007692
```
* Test Case 2
```text
STATS:
PID:1003      Waiting Time:33      Turnaround:93
PID:1006      Waiting Time:118     Turnaround:295
PID:1007      Waiting Time:204     Turnaround:372
PID:1004      Waiting Time:321     Turnaround:479
PID:1005      Waiting Time:216     Turnaround:484
PID:1002      Waiting Time:289     Turnaround:692
PID:1008      Waiting Time:0       Turnaround:280
PID:1001      Waiting Time:30      Turnaround:2470
Average Waiting Time: 151.375000
Average Turnaround Time: 645.625000
Average Throughput: 0.003239
```
* Test Case 3
```text
STATS:
PID:1003      Waiting Time:15     Turnaround:200
PID:1004      Waiting Time:72     Turnaround:482
PID:1002      Waiting Time:0      Turnaround:1000
PID:1001      Waiting Time:50     Turnaround:2050
Average Waiting Time: 34.250000
Average Turnaround Time: 933.000000
Average Throughput: 0.001951
```
* Test Case 4
```text
STATS:
PID:1004      Waiting Time:43     Turnaround:201
PID:1003      Waiting Time:61     Turnaround:271
PID:1006      Waiting Time:32     Turnaround:363
PID:1005      Waiting Time:33     Turnaround:427
PID:1007      Waiting Time:119    Turnaround:525
PID:1002      Waiting Time:183    Turnaround:1487
PID:1008      Waiting Time:0      Turnaround:1080
PID:1001      Waiting Time:15     Turnaround:25855
Average Waiting Time: 60.750000
Average Turnaround Time: 3776.125000
Average Throughput: 0.000309
```

## Usage
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

Once the script finished running, you will notice an output file has bee created in this format
```
output-{input filename}
```