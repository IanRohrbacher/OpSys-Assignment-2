# OpSys-Assignment-2
Fall 2024 Operating Systems (CS-33211-001) Assignment #2
>*Created, ran, and tested on Kent State University's wasp/hornet sever*

## Assignment 2 Details
Considering a system with five processes P0 through P4 and three resources of type A, B, C. Resource type A has 10 instances, B has 5 instances and type C has 7 instances. Suppose at time t0 following snapshot of the system has been taken: Implement the Banker’s algorithm to answer the following question:
| Process | Allocation | Max | Available |
| ----------- | ----------- | ----------- | ----------- |
|   | A B C | A B C | A sB C |
| P0 | 0 0 1 | 7 5 3 | 3 3 2 |
| P1 | 2 0 0 | 3 2 2 |   |
| P2 | 3 0 2 | 9 0 2 |   |
| P3 | 2 1 1 | 2 2 2 |   |
| P4 | 0 0 2 | 4 3 3 |   |

Is the system in a safe state? If Yes, then what is the safe sequence?

---

This code takes input from a txt file and produces if the system is in a safe state, with the resulting sequence, or if it's not in a safe state


## Getting started
### Installing
Copy files onto a Linux/Unix machine with C/C++ installed.

### Running
**DO NOT remove files from the input folder! You can add your own, but it must follow a format defined in Features**
- To run the program with the example txt files use 'make runDefult'.
- To run custom input.txt files use 'ARGS=filename.txt make run'.
- To clear .o files use 'make clear'
  
## Features
This file takes input from files found within the input folder. To create your own input file, you must follow the format below
- file must be a .txt
- line one - 'n=number'
- line two - 'm=number'
- line three = 'availableResource={size of m}'
- then every next pair of lines up to n pairs - allocation0={size of m} maxAllocation0={size of m}

---

>Example:
```{txt}
n=5
m=3
availableResource={10,5,7}
allocation0={0,1,0}
maxAllocation0={7,5,3}
allocation1={2,0,0}
maxAllocation1={3,2,2}
allocation2={3,0,2}
maxAllocation2={9,0,2}
allocation3={2,1,1}
maxAllocation3={2,2,2}
allocation4={0,0,2}
maxAllocation4={4,3,3}
```

## Example of Execution
```{bash}
[$PATH]$ ARGS=input1.txt make run
./main input1.txt 
n:5 | m:3 | Available Resources:{3, 3, 2} |
P0 | Allocation:{0, 1, 0} | Max:{7, 5, 3} |
P1 | Allocation:{2, 0, 0} | Max:{3, 2, 2} |
P2 | Allocation:{3, 0, 2} | Max:{9, 0, 2} |
P3 | Allocation:{2, 1, 1} | Max:{2, 2, 2} |
P4 | Allocation:{0, 0, 2} | Max:{4, 3, 3} |
This System Is In A Save State!
The Following Is The Safe Sequence
P1 -> P3 -> P4 -> P0 -> P2
```

## Contributing
This is a finished assignment uploaded to github for a grade. Do NOT copy and paste my work but feel free to use it as a reference.

## Licensing
The code in this project is licensed under MIT license.
