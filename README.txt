Author: Philip Amwata

Source Code Description
_______________________
driver.cpp - driver file for the program
volimage.cpp - contains method and variablble definitions for the program
volimage.hpp - header file that contains declaration of variables and methods for volimage.cpp

NOTE: used .hpp due to some issues with formatting and syntax identification with my IDE

Running The Application
_______________________
use make to compile and link.
./volimage MRI - default read image
./volimage MRI -x i fileName - extraction
./volimage MRI -d i j fileName - compute difference map

Makefile Instructions
_______________________
make - compile and link driver.cpp, volimage.cpp, driver.o and volimage.o into volimage executable
make clean - remove all .o, .dat, .raw files and the executable file from current directory
make run - ./volimage MRI - the default case run 

Project Structure
_______________________
/AMWPHI001
    driver.cpp
    volimage.cpp
    volimage.hpp
    README.txt
    Makefile
    viewer.py
    diffmap.py
    /MRI
        MRI.dat
        MRI1.raw
        .....
    