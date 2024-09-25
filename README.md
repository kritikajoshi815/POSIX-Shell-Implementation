# POSIX Shell Implementation

## Description
This project is a custom shell implementation in C++ that handles basic shell functionalities.

## Installation
1. Download the zipped file.
2. Compile the file using make main command
3. Execute the code using ./a.out
4. Use exit to exit from this terminal and return back to the original terminal.

## Features and Usage
The following commands are implemented using this project.
1. The terminal displays the name of the user and system name.

## cd.cpp
Command helps to change within various directory and various flags like “.”, “..” and “~” are implemented.

Assumptions: In case when the control is in root directory of this POSIX shell, then cd .. will print the absolute path till the current directory in the system.

Working: chdir() is used to change the dirctories within cd

## echo.cpp
Command prints the command given after echo using cout.

## pwd.cpp
To print the current working directory path
Assumptions: When control is in this termianl pwd prints the absolute path 
             In other case relative path w.r.t. this terminal is printed.

Working: It uses getcwd() to get pwd path.

## ls.cpp
To print the list of directories and files present in current directory
Various flags like: -a, -l, ., .. , ~ , -a -l, -la, -al are implemented
Working: It is implemented using opendir(), readdir(), closedir() fuctions.

## System Commands 
1. Foreground Processes: Using a simple command in this terminal, the forgound process begins and when the process gets complete, after that the control returns back to the terminal.

2. Bakground Processes: They are invoked with an '&' symbol. The control immediately comes back to terminal and process id of the process is printed.

Working: These commands are executed using fork(), execvp() and waitpid() system calls. 
         Foregound process waits for the child process to complete using waitpid().

## pinfo.cpp
Assumptions: When the control is within the current termianl, it prints the process information of the terminal itself.
             Provide a process id along with pinfo, so to fetch the details about the process.
             Foreground processes are represented by a '+'.

Usage: It informs about the process status in terms of status codes link R, S, Z, T.
       It also informs about the amount of memory used by the process in kilobytes(KB).
       Path of the executable file is also represented.

## search.cpp
Assumptions: Give the name of the file or folder to be searched after search.

Working: It uses opendir(), readdir(), closedir() to open and read for the files or folder present within a directory.
         It recursively searches for the file or folder with the current directory.

## io.cpp
Working: Based on the command given, the code assigns the input and output file names, and using fork() and execvp() to execute the command, along with the use of dup2 to make changes to output file and to always take input from input file.

