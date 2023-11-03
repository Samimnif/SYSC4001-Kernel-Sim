# Assignement 1
## Details
For this assignement we created a FCFS Kernel Simulator. It reads data from csv file and ouputs a file with the states changes details for each process. The terminal will also print more detailed information of each process for each clock cycle. We also included a waiting time stats at the end of the program.
## Files

* main.c
* main
* test_case_1.csv (Contains test case 1 from Brightspace)
* test_case_2.csv (Contains test case 2 from Brightspace)
* test_case_3.csv (Contains test case 3 from Slides example)
* test1.sh
* test2.sh
* test3.sh

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