# Process
A process is a program in execution.
1. Old systems could only load and execute one program at a time,meaning if you were to run another program, you have to unload the previous program and load a new one to be executed.
2. Multisystems allowed loading of multiple programs and executing them all concurrently.
3. we can say that a system is a collection of processes.

More reads: [Process](https://en.wikipedia.org/wiki/Process_(computing))

## Process concepts
### Process structure.
Process is made up of 4 structures, the text section, the data section, the heap section and the stack section

![alt text](https://github.com/backendpapa/Operating-system-concept/blob/main/Process/process.png?raw=true)

- **The Text Section:** This section contains executable codes or the program code.
- **The Data Section:** contains global variables that have been set in the program code
- **THe Heap Section:** is the dynamic memory allocated to the process.
- **The Stack Section:** acts as a temporary storage for executing function parameters, variables and memory addresses.

The Text and Data section are static while the Heap and Stack section are dynamic. When a function is called, an activation record which contains parameters of the called function is pushed to the stack, once usage is completed and control is returned back to the system, the activation record is popped out of the stack.

The addition and removal of activation records affects the dynamic memory allocation such that when a record is pushed to the stack, the Heap size grows (memory allocated increase, when the record is popped of the stack, the Heap shrinks as it returns memory to the system.

![alt text](https://github.com/backendpapa/Operating-system-concept/blob/main/Process/process-structure.png?raw=true)



<code> $ bash size.sh </code>
This code finds the size structure of an executable
```
text    data     bss     dec     hex filename
1603     604      12    2219     8ab ./process-example
```

### Process state
A process can belong to any of the 5 states below. it could differ in other Operating System, but the concept is the same throughout
1. **New:** A new process is created at the state, it is yet to be assigned a processor for execution.
2. **Ready:** The new process is assigned to a processor at this state and is ready to run or execute.
3. **Running:** The Assigned process is executing at this state
4. **Waiting:** If the process needs to access an I/O like an external drive, an external keyboard, it enters this waiting state, at this point, the processor is reassigned so other processes can use the processor.once I/O is completed, it enters into the Ready state where it is reassinged a processor and starts executing(Running) again
5. **Termination:** The program has completed its execution or there is a sudden error that triggered its termination.

![alt text](https://github.com/backendpapa/Operating-system-concept/blob/main/Process/process-state.png?raw=true)

More reads: [Process state](https://en.wikipedia.org/wiki/Process_state)

### Process control block
A process control block is a type of data structure that acts as a data repository for a particular process. It stores a lot of information regarding a process.

The following information found in a PCB includes:
1. **Process state:** The can be any of the 5 states- New, Waiting, Ready, Running, Terminated
2. **Program number:** Each processes are assigned a number for identification
3. **Program counter:** The counter increments to determine which next address of instruction is to be executed for a particular instruction.
4. **CPU Registers:** Sets where the process information is to be saved to.
5. **CPU Scheduling:** Determines when a process is allocated the processor.
6. **Memory management information:**: Contains information such as the memory table
7. **Accounting management:** Contains information about processor used,time limit etc
8. **I/0 status:** Contain information about I/O devices allocated to the process.

![alt text](https://github.com/backendpapa/Operating-system-concept/blob/main/Process/pcb.png?raw=true)

More reads: [Process control block](https://en.wikipedia.org/wiki/Process_control_block)

### Thread
A thread implies execution of instructions in a process. A single thread means there is just a single instruction being executed in a process, while multithread means multiple instructions are being executed in a process in real time. This is done in parallel as it is more efficient in multicore PCs

