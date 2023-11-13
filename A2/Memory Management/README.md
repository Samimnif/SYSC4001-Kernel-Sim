# Assignement 2
## Memory Management
* Test Cases from 1 - 4 are for **_testing_**
* Test Cases From 5 - 14 are for **_Analysis_**
### Results
#### Test Cases
* Test Case 1
```text
STATS:
PID:1001      Waiting Time:0     Turnaround:100
PID:1002      Waiting Time:0     Turnaround:200
PID:1003      Waiting Time:0     Turnaround:110
PID:1004      Waiting Time:10     Turnaround:120
Average Waiting Time: 2.500000
Average Turnaround Time: 132.500000
Average Throughput: 0.007692
```
* Test Case 2 
```text
STATS:
PID:1004      Waiting Time:101     Turnaround:259
PID:1006      Waiting Time:29     Turnaround:206
PID:1007      Waiting Time:44     Turnaround:375
PID:1002      Waiting Time:180     Turnaround:583
PID:1003      Waiting Time:9     Turnaround:652
PID:1008      Waiting Time:0     Turnaround:280
PID:1001      Waiting Time:110     Turnaround:2550
PID:1005      Waiting Time:0     Turnaround:2719
Average Waiting Time: 59.125000
Average Turnaround Time: 953.000000
Average Throughput: 0.002838
```
* Test Case 3
```text
STATS:
PID:1003      Waiting Time:15     Turnaround:200
PID:1004      Waiting Time:32     Turnaround:643
PID:1002      Waiting Time:0     Turnaround:1000
PID:1001      Waiting Time:50     Turnaround:2050
Average Waiting Time: 24.250000
Average Turnaround Time: 973.250000
Average Throughput: 0.001951
```
* Test Case 4
```text
STATS:
PID:1003      Waiting Time:24     Turnaround:234
PID:1004      Waiting Time:24     Turnaround:416
PID:1006      Waiting Time:10     Turnaround:341
PID:1005      Waiting Time:21     Turnaround:735
PID:1007      Waiting Time:3     Turnaround:1145
PID:1002      Waiting Time:208     Turnaround:1512
PID:1008      Waiting Time:4     Turnaround:1084
PID:1001      Waiting Time:12     Turnaround:25852
Average Waiting Time: 38.250000
Average Turnaround Time: 3914.875000
Average Throughput: 0.000309
```
<hr>

#### Analysis Using _test_memory_1.csv_ Settings
* **Test Case 5 (LARGEST-SMALLEST)**
```
STATS:
PID:1003      Waiting Time:13     Turnaround:23
PID:1004      Waiting Time:52     Turnaround:225
PID:1007      Waiting Time:17     Turnaround:229
PID:1001      Waiting Time:27     Turnaround:367
PID:1005      Waiting Time:2     Turnaround:406
PID:1006      Waiting Time:19     Turnaround:646
PID:1002      Waiting Time:98     Turnaround:955
PID:1008      Waiting Time:0     Turnaround:226
Average Waiting Time: 28.500000
Average Turnaround Time: 384.625000
Average Throughput: 0.006525
```
* **Test Case 6 (SMALLEST-LARGEST)**
```
STATS:
PID:1001      Waiting Time:0     Turnaround:340
PID:1003      Waiting Time:19     Turnaround:368
PID:1004      Waiting Time:4     Turnaround:522
PID:1002      Waiting Time:116     Turnaround:606
PID:1006      Waiting Time:0     Turnaround:728
PID:1005      Waiting Time:37     Turnaround:738
PID:1007      Waiting Time:0     Turnaround:951
PID:1008      Waiting Time:0     Turnaround:278
Average Waiting Time: 22.000000
Average Turnaround Time: 566.375000
Average Throughput: 0.006260
```
* **Test Case 7 (RANDOM)**
```
STATS:
PID:1006      Waiting Time:51     Turnaround:271
PID:1007      Waiting Time:128     Turnaround:340
PID:1001      Waiting Time:118     Turnaround:458
PID:1003      Waiting Time:19     Turnaround:486
PID:1004      Waiting Time:4     Turnaround:640
PID:1002      Waiting Time:234     Turnaround:724
PID:1005      Waiting Time:0     Turnaround:819
PID:1008      Waiting Time:0     Turnaround:226
Average Waiting Time: 69.250000
Average Turnaround Time: 495.500000
Average Throughput: 0.006525
```
* **Test Case 8 (HIGH CONSTANT)** 
```
STATS:
PID:1001      Waiting Time:0     Turnaround:340
PID:1002      Waiting Time:0     Turnaround:830
PID:1003      Waiting Time:0     Turnaround:840
PID:1004      Waiting Time:0     Turnaround:990
PID:1005      Waiting Time:0     Turnaround:1169
PID:1006      Waiting Time:0     Turnaround:1390
PID:1007      Waiting Time:0     Turnaround:1603
PID:1008      Waiting Time:0     Turnaround:930
Average Waiting Time: 0.000000
Average Turnaround Time: 1011.500000
Average Throughput: 0.004145
```
* **Test Case 9 (LOW CONSTANT)**
```
STATS:
PID:1003      Waiting Time:33     Turnaround:43
PID:1004      Waiting Time:136     Turnaround:286
PID:1001      Waiting Time:80     Turnaround:420
PID:1005      Waiting Time:75     Turnaround:350
PID:1006      Waiting Time:54     Turnaround:464
PID:1007      Waiting Time:63     Turnaround:596
PID:1002      Waiting Time:255     Turnaround:745
PID:1008      Waiting Time:0     Turnaround:226
Average Waiting Time: 87.000000
Average Turnaround Time: 391.250000
Average Throughput: 0.006525
```
<hr>

#### Analysis Using _test_memory_2.csv_ Settings
* **Test Case 10 (LARGEST-SMALLEST)**
```
STATS:
PID:1003      Waiting Time:33     Turnaround:43
PID:1004      Waiting Time:106     Turnaround:299
PID:1007      Waiting Time:77     Turnaround:289
PID:1001      Waiting Time:77     Turnaround:417
PID:1006      Waiting Time:19     Turnaround:557
PID:1005      Waiting Time:89     Turnaround:567
PID:1002      Waiting Time:266     Turnaround:756
PID:1008      Waiting Time:0     Turnaround:226
Average Waiting Time: 83.375000
Average Turnaround Time: 394.250000
Average Throughput: 0.006525
```
* **Test Case 11 (SMALLEST-LARGEST)**
```
STATS:
PID:1003      Waiting Time:33     Turnaround:43
PID:1004      Waiting Time:64     Turnaround:257
PID:1001      Waiting Time:4     Turnaround:344
PID:1006      Waiting Time:19     Turnaround:484
PID:1005      Waiting Time:58     Turnaround:494
PID:1002      Waiting Time:205     Turnaround:695
PID:1007      Waiting Time:29     Turnaround:726
PID:1008      Waiting Time:0     Turnaround:226
Average Waiting Time: 51.500000
Average Turnaround Time: 408.625000
Average Throughput: 0.006525
```
* **Test Case 12 (RANDOM)**
```
STATS:
PID:1003      Waiting Time:33     Turnaround:43
PID:1004      Waiting Time:106     Turnaround:299
PID:1007      Waiting Time:77     Turnaround:289
PID:1001      Waiting Time:77     Turnaround:417
PID:1006      Waiting Time:19     Turnaround:557
PID:1005      Waiting Time:89     Turnaround:567
PID:1002      Waiting Time:266     Turnaround:756
PID:1008      Waiting Time:0     Turnaround:226
Average Waiting Time: 83.375000
Average Turnaround Time: 394.250000
Average Throughput: 0.006525
```
* **Test Case 13 (HIGH CONSTANT)** 
```
STATS:
PID:1003      Waiting Time:33     Turnaround:43
PID:1004      Waiting Time:64     Turnaround:257
PID:1001      Waiting Time:4     Turnaround:344
PID:1006      Waiting Time:19     Turnaround:484
PID:1005      Waiting Time:58     Turnaround:494
PID:1002      Waiting Time:205     Turnaround:695
PID:1007      Waiting Time:29     Turnaround:726
PID:1008      Waiting Time:0     Turnaround:226
Average Waiting Time: 51.500000
Average Turnaround Time: 408.625000
Average Throughput: 0.006525
```
* **Test Case 14 (LOW CONSTANT)**
```
STATS:
PID:1003      Waiting Time:33     Turnaround:43
PID:1004      Waiting Time:136     Turnaround:286
PID:1001      Waiting Time:80     Turnaround:420
PID:1005      Waiting Time:75     Turnaround:350
PID:1006      Waiting Time:54     Turnaround:464
PID:1007      Waiting Time:63     Turnaround:596
PID:1002      Waiting Time:255     Turnaround:745
PID:1008      Waiting Time:0     Turnaround:226
Average Waiting Time: 87.000000
Average Turnaround Time: 391.250000
Average Throughput: 0.006525
```