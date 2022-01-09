# Operating-system-concept

# Process
A process is a program in execution.
1. Old systems could only load and execute one program at a time,meaning if you were to run another program, you have to unload the previous program and load a new one to be executed.
2. Multisystems allowed loading of multiple programs and executing them all concurrently.
3. we can say that a system is a collection of processes.

## Process structure.
Process is made up of 4 structures, the text section, the data section, the heap section and the stack section

![alt text](https://github.com/backendpapa/Operating-system-concept/blob/main/process.png?raw=true)

- **The Text Section:** This section contains executable codes or the program code.
- **The Data Section:** contains global variables that have been set in the program code
- **THe Heap Section:** is the dynamic memory allocated to the process.
- **The Stack Section:** acts as a temporary storage for executing function parameters, variables and memory addresses.

The Text and Data section are static while the Heap and Stack section are dynamic. When a function is called, an activation record which contains parameters of the called function is pushed to the stack, once usage is completed and control is returned back to the system, the activation record is popped out of the stack.

The addition and removal of activation records affects the dynamic memory allocation such that when a record is pushed to the stack, the Heap size grows (memory allocated increase, when the record is popped of the stack, the Heap shrinks as it returns memory to the system.

![alt text](https://github.com/backendpapa/Operating-system-concept/blob/main/process-structure.png?raw=true)



<code> $ bash size.sh </code>
This code finds the size structure of an executable
```
text    data     bss     dec     hex filename
1603     604      12    2219     8ab ./process-example
```