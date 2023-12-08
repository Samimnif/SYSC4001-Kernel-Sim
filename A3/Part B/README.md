# Assignement 3
## Details
For this assignement we created an ATM service.
The files are:
* **atm.c** - interacts with the user and db_server (acts as the bridge)
* **db_server.c** - mostly changes the database data, receives messages from the db_editor and the atm.c
* **db_editor.c** - receives inputs from user and sends it to db_server to add them to databse.
<br><br>
The atm_key is used to save the message token.<br>

## Usage
You hae to firstly open two terminal windows
Then run the atm service in teh first terminal.
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
