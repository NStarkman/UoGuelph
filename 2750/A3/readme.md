# Assignemnt 3: CIS*2750 Molecule SVG SQL Library

## Description

This program is a library that can be used to store and manipulate molecules. The library is written in Python and SQL and the server is written in Python. The library is used to store molecules in a database It can also produce the SVG image of a molecule. The server is used to display the SVG image of a molecule, from a file instead of a database.

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
    python3 MolDisplay.py
    python3 molSql.py
```


## Author Information

* Nathan Starkman
* 112781
* nstarkma@uoguelph.ca
