# Everything you need to know to start coding your own shell

In this Repo  the exercises are everything that is needed for us to start coding our own simple_shell.

## EXERCISES

## PID & PPID

### 0. getppid
- Write a program that prints the PID of the parent process. 
- Run your program several times within the same shell. 
- It should be the same. Does echo $$ print the same value?
- filename: 

### 1. /proc/sys/kernel/pid_max
- Write a shell script that prints the maximum value a process ID can be.
- filename:

## Arguments

### 0. av
- Write a program that prints all the arguments, without using ac.
- filename:

### 1. Read line
- Write a program that prints "$ ", wait for the user to enter a command, prints it on the next line.
- man 3 getline
- filename:

### 2. command line to av
- Write a function that splits a string and returns an array of each word of the string
- man strtok
- filename:

## Executing a program
