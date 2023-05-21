# Assignemnt 2: CIS*2750 Molecule SVG Creator

## Description

Code that turns my original code into a Python Library. The library is then used to create an SVG image of specific molecules. The data is taken from an SDF file and the SVG is created using the Python library and python code in molDisplay. It is then displayed on my local server.

## Running

To run the program, run the following command in the terminal:

NOTE: This program needs a specific command to have been run before it can run:

``` bash
    export LD_LIBRARY_PATH=.
```

Without this command, the program will encounter an error. I have been told that I can assume that this command has been run. However, I have mentioned it here just in case.

NOTE: The python path in the makefile currently uses Python 3.7m, the type for the school server. On my computer, I used Python 3.10. If you are using Python 3.10, you will need to change the path in the makefile to the path of your Python 3.10, or any other Python installation.

```C
    make
```

This will load the library and the server at localhost:57811. The server will display the SVG image of the molecule chosen.

## Author Information

* Nathan Starkman
* 112781
* nstarkma@uoguelph.ca
