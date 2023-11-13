# Assignement 2
## Round Robin Algorithm
In main.c we implemented the Round Robin Algorithm with 100ms timeout(1s) -> 1 CPU clock cycle.
### Results
* Test Case 1
```text
STATS:
PID:1001      Waiting Time:0     Turnaround:100
PID:1002      Waiting Time:0     Turnaround:100
PID:1003      Waiting Time:49     Turnaround:99
PID:1004      Waiting Time:50     Turnaround:100
Average Waiting Time: 24.750000
Average Turnaround Time: 99.750000
Average Throughput: 0.008000
```
* Test Case 2
```text
STATS:
PID:1003      Waiting Time:28     Turnaround:38
PID:1004      Waiting Time:169     Turnaround:219
PID:1001      Waiting Time:366     Turnaround:466
PID:1005      Waiting Time:388     Turnaround:488
PID:1006      Waiting Time:389     Turnaround:489
PID:1007      Waiting Time:390     Turnaround:490
PID:1002      Waiting Time:459     Turnaround:709
PID:1008      Waiting Time:0     Turnaround:100
Average Waiting Time: 273.625000
Average Turnaround Time: 374.875000
Average Throughput: 0.007273
```
* Test Case 3
```text
STATS:
PID:1001      Waiting Time:0     Turnaround:100
PID:1002      Waiting Time:0     Turnaround:100
PID:1003      Waiting Time:49     Turnaround:99
PID:1004      Waiting Time:50     Turnaround:100
Average Waiting Time: 24.750000
Average Turnaround Time: 99.750000
Average Throughput: 0.008000
```
*Test Case 4
```text
STATS:
PID:1003      Waiting Time:18     Turnaround:28
PID:1004      Waiting Time:77     Turnaround:127
PID:1005      Waiting Time:305     Turnaround:405
PID:1006      Waiting Time:306     Turnaround:406
PID:1007      Waiting Time:307     Turnaround:407
PID:1002      Waiting Time:362     Turnaround:612
PID:1008      Waiting Time:1     Turnaround:101
PID:1001      Waiting Time:3     Turnaround:25843
Average Waiting Time: 172.375000
Average Turnaround Time: 3491.125000
Average Throughput: 0.000310
```
* Test Case 5 **(CPU BOUND)**
```
STATS:
PID:1003      Waiting Time:28     Turnaround:38
PID:1004      Waiting Time:169     Turnaround:219
PID:1001      Waiting Time:366     Turnaround:466
PID:1005      Waiting Time:388     Turnaround:488
PID:1006      Waiting Time:389     Turnaround:489
PID:1007      Waiting Time:390     Turnaround:490
PID:1002      Waiting Time:459     Turnaround:709
PID:1008      Waiting Time:0     Turnaround:100
Average Waiting Time: 273.625000
Average Turnaround Time: 374.875000
Average Throughput: 0.007273
```
* Test Case 6 **(I/O Bound )**
```
STATS:
PID:1003      Waiting Time:28     Turnaround:38
PID:1004      Waiting Time:169     Turnaround:219
PID:1001      Waiting Time:366     Turnaround:466
PID:1005      Waiting Time:388     Turnaround:488
PID:1006      Waiting Time:389     Turnaround:489
PID:1007      Waiting Time:390     Turnaround:490
PID:1002      Waiting Time:459     Turnaround:709
PID:1008      Waiting Time:0     Turnaround:100
Average Waiting Time: 273.625000
Average Turnaround Time: 374.875000
Average Throughput: 0.007273
```
* Test Case 7 **(Balanced)**
```
STATS:
PID:1003      Waiting Time:28     Turnaround:38
PID:1004      Waiting Time:169     Turnaround:219
PID:1001      Waiting Time:366     Turnaround:466
PID:1005      Waiting Time:388     Turnaround:488
PID:1006      Waiting Time:389     Turnaround:489
PID:1007      Waiting Time:390     Turnaround:490
PID:1002      Waiting Time:459     Turnaround:709
PID:1008      Waiting Time:0     Turnaround:100
Average Waiting Time: 273.625000
Average Turnaround Time: 374.875000
Average Throughput: 0.007273
```