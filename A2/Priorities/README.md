# Assignement 2
## External Priorities (no preemption) Algorithm
In main.c we implemented the External Priorities (no preemption) Algorithm.
### Results
* Test Case 1
```text
STATS:
PID:1001      Waiting Time:0     Turnaround:100
PID:1002      Waiting Time:0     Turnaround:200
PID:1003      Waiting Time:10     Turnaround:120
PID:1004      Waiting Time:0     Turnaround:110
Average Waiting Time: 2.500000
Average Turnaround Time: 132.500000
Average Throughput: 0.007843
```
* Test Case 2
```text
STATS:
PID:1001      Waiting Time:140     Turnaround:2580
PID:1002      Waiting Time:343     Turnaround:746
PID:1003      Waiting Time:313     Turnaround:373
PID:1004      Waiting Time:212     Turnaround:370
PID:1005      Waiting Time:178     Turnaround:446
PID:1006      Waiting Time:62     Turnaround:239
PID:1007      Waiting Time:27     Turnaround:195
PID:1008      Waiting Time:0     Turnaround:280
Average Waiting Time: 159.375000
Average Turnaround Time: 653.625000
Average Throughput: 0.006250
```
* Test Case 3
```text
STATS:
PID:1004      Waiting Time:77     Turnaround:487
PID:1003      Waiting Time:15     Turnaround:200
PID:1002      Waiting Time:0     Turnaround:1000
PID:1001      Waiting Time:50     Turnaround:2050
Average Waiting Time: 35.500000
Average Turnaround Time: 934.250000
Average Throughput: 0.001951
```
* Test Case 4
```text
STATS:
PID:1008      Waiting Time:5     Turnaround:1085
PID:1007      Waiting Time:171     Turnaround:577
PID:1006      Waiting Time:56     Turnaround:387
PID:1005      Waiting Time:11     Turnaround:405
PID:1004      Waiting Time:39     Turnaround:197
PID:1003      Waiting Time:24     Turnaround:234
PID:1002      Waiting Time:111     Turnaround:1415
PID:1001      Waiting Time:3     Turnaround:25843
Average Waiting Time: 52.500000
Average Turnaround Time: 3767.875000
Average Throughput: 0.000310
```
* Test Case 5 **(CPU BOUND)**
```
STATS:
PID:1001      Waiting Time:85     Turnaround:1135
PID:1002      Waiting Time:129     Turnaround:1212
PID:1003      Waiting Time:10     Turnaround:60
PID:1004      Waiting Time:43     Turnaround:336
PID:1005      Waiting Time:122     Turnaround:822
PID:1006      Waiting Time:30     Turnaround:610
PID:1007      Waiting Time:26     Turnaround:606
PID:1008      Waiting Time:13     Turnaround:398
Average Waiting Time: 57.250000
Average Turnaround Time: 647.375000
Average Throughput: 0.005722
```
* Test Case 6 **(I/O Bound )**
```
STATS:
PID:1001      Waiting Time:445     Turnaround:1025
PID:1002      Waiting Time:274     Turnaround:724
PID:1003      Waiting Time:28     Turnaround:38
PID:1004      Waiting Time:237     Turnaround:392
PID:1005      Waiting Time:205     Turnaround:505
PID:1006      Waiting Time:105     Turnaround:345
PID:1007      Waiting Time:50     Turnaround:270
PID:1008      Waiting Time:0     Turnaround:280
Average Waiting Time: 168.000000
Average Turnaround Time: 447.375000
Average Throughput: 0.006250
```
* Test Case 7 **(Balanced)**
```
STATS:
PID:1001      Waiting Time:388     Turnaround:728
PID:1002      Waiting Time:337     Turnaround:827
PID:1003      Waiting Time:25     Turnaround:35
PID:1004      Waiting Time:332     Turnaround:482
PID:1005      Waiting Time:108     Turnaround:383
PID:1006      Waiting Time:26     Turnaround:246
PID:1007      Waiting Time:64     Turnaround:276
PID:1008      Waiting Time:0     Turnaround:226
Average Waiting Time: 160.000000
Average Turnaround Time: 400.375000
Average Throughput: 0.006525
```