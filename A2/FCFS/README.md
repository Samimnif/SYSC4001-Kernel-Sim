# Assignement 2
## Details
For this assignement we created a FCFS Kernel Simulator. It reads data from csv file and ouputs a file with the states changes details for each process. The terminal will also print more detailed information of each process for each clock cycle. We also included a waiting time stats at the end of the program.
### Results
* PART 1 C
```
STATS:
PID:1001      Waiting Time:0     Turnaround:18
PID:1002      Waiting Time:15     Turnaround:22
PID:1003      Waiting Time:17     Turnaround:29
PID:1004      Waiting Time:26     Turnaround:36
PID:1005      Waiting Time:34     Turnaround:43
Average Waiting Time: 18.400000
Average Turnaround Time: 29.600000
Average Throughput: 0.089286
```
* PART 1 D
```
STATS:
PID:1002      Waiting Time:9     Turnaround:22
PID:1005      Waiting Time:21     Turnaround:38
PID:1004      Waiting Time:23     Turnaround:42
PID:1003      Waiting Time:24     Turnaround:47
PID:1001      Waiting Time:23     Turnaround:58
Average Waiting Time: 20.000000
Average Turnaround Time: 41.400002
Average Throughput: 0.086207
```
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
* Test Case 5 **(CPU BOUND)**
```
STATS:
PID:1003      Waiting Time:11     Turnaround:61
PID:1004      Waiting Time:58     Turnaround:351
PID:1006      Waiting Time:43     Turnaround:623
PID:1007      Waiting Time:52     Turnaround:632
PID:1005      Waiting Time:104     Turnaround:804
PID:1001      Waiting Time:56     Turnaround:1106
PID:1002      Waiting Time:115     Turnaround:1198
PID:1008      Waiting Time:19     Turnaround:404
Average Waiting Time: 57.250000
Average Turnaround Time: 647.375000
Average Throughput: 0.005698
```
* Test Case 6 **(I/O Bound )**
```
STATS:
PID:1003      Waiting Time:43     Turnaround:53
PID:1004      Waiting Time:297     Turnaround:452
PID:1006      Waiting Time:135     Turnaround:375
PID:1007      Waiting Time:230     Turnaround:450
PID:1005      Waiting Time:215     Turnaround:515
PID:1002      Waiting Time:289     Turnaround:739
PID:1001      Waiting Time:175     Turnaround:755
PID:1008      Waiting Time:0     Turnaround:280
Average Waiting Time: 173.000000
Average Turnaround Time: 452.375000
Average Throughput: 0.006250
```
* Test Case 7 **(Balanced)**
```
STATS:
PID:1003      Waiting Time:33     Turnaround:43
PID:1004      Waiting Time:277     Turnaround:427
PID:1006      Waiting Time:153     Turnaround:373
PID:1007      Waiting Time:248     Turnaround:460
PID:1001      Waiting Time:230     Turnaround:570
PID:1005      Waiting Time:225     Turnaround:500
PID:1002      Waiting Time:329     Turnaround:819
PID:1008      Waiting Time:0     Turnaround:226
Average Waiting Time: 186.875000
Average Turnaround Time: 427.250000
Average Throughput: 0.006525
```