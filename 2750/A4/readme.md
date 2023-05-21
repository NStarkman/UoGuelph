# Assignemnt 4: CIS*2750 Molecule Webserver and Library

## Description

This is the final code that encompasses all of the work done for this class. It is a webserver that allows users to search for molecules in a database, and view them. It also allows users to add molecules to the database. The webserver is written in Python, and the database is written in SQLite/Python. The C library is used to manipulate the molecules. Finally, there is HTML, CSS, and JavaScript used to create and control the webpages.

## Running

To run the program, run the following command in the terminal:

NOTE: This program needs a specific command to have been run before it can run:

``` bash
    export LD_LIBRARY_PATH=`.`
```

Without this command, the program will encounter an error. I have been told that I can assume that this command has been run. However, I have mentioned it here just in case.

NOTE: The python path in the makefile currently uses Python 3.7m, the type for the school server. On my computer, I used Python 3.10. If you are using Python 3.10, you will need to change the path in the makefile to the path of your Python 3.10, or any other Python installation.

```C
    make
```

This will create all required information for the program to run. It will create the C library. The two python programs, MolDisplay and molSql are not run automatially and are not executeable. If you want to run them regardless, you can run the following commands:

```C
    python3 server.py 57811
```

## Author Information

* Nathan Starkman
* 112781
* nstarkma@uoguelph.ca
