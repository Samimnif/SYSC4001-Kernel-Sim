# Assignement 3
## Details
For this assignement we created an ATM service.
The files are:
* **atm.c** - interacts with the user and db_server (acts as the bridge)
* **db_server.c** - mostly changes the database data, receives messages from the db_editor and the atm.c
* **db_editor.c** - receives inputs from user and sends it to db_server to add them to databse.
<br><br>
The atm_key is used to save the message token.<br>

## Assumptions
We assume that whoever is using the db_editor.c is a trained professional.
Meaning they know that they have to:
* Put exact 5 digits for the Account number. Anything more will not be accepted, and instead will take the frst 5 digits of the input.
* Put 3 digits for account PIN. Anything more will not be accepted, and instead will take the frst 3 digits of the input.
* Put any integer/float in he funds section.
<br>

We assume that whoever is using the db_server.c, is going to consider the follwoing:
* Put exact 5 digits for the Account number. If they put more than 5, an error will be displayed. If less than 5 then the leading numbers will be filled with zeroes. For example, if the user enters 123, it will be considered as 00123.
* Put 3 digits for account PIN. If the user enters more or less than 3 digits, it will give an error and return to step 1 (Asking Account number).
* Select one of the two options: 1 for Balance display or 2 for withdraw function.

## Best Practices
* You will notice there is a data_struct.h file that contains all the defined structs, that are used across all three files.
* We included all the necessary comments and assumptions in this README and in the code file description (top of the file).

## Usage
Make sure you compile all threee files: atm.c, db_server.c and db_editor.c <br>
You have to firstly open two terminal windows
Then run the atm service in the first terminal.
```bash
./atm 
```
Then run the db_editor in teh second terminal
```bash
./db_editor
```

In case you get a permission error for the bash files, please change
file permissions
```bash
chmod 777 {filename}
```
