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
```
* Test Case 3
```text
STATS:
PID:2      Waiting Time:4     Turnaround:8
PID:3      Waiting Time:2     Turnaround:7
PID:1      Waiting Time:6     Turnaround:13
Average Waiting Time: 4.000000
```