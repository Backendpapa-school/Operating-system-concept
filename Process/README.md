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


![alt text](https://github.com/backendpapa/Operating-system-concept/blob/main/Process/thread.png?raw=true)

More reads: [Thread](https://en.wikipedia.org/wiki/Thread_(computing))

## Process scheduling
Process scheduling is a situation tha occurs when there are excess processes available than the cores.The excess processes are resheduled to wait until the cores are free for use.
This is prevalent in multicore system as a core can only execute one process at a time. SOme process can be CPU bound(**doing computations**) or I/O bound(**Less computation**)

### Scheduling queues
A scheduling queues contains processes that are ready to be executed. Its a linked list kind of data structure in which one process have a pointer to the next process
There are two types of scheduling queues:
1. **Ready queue:** Stores PCB's of processes ready to be waiting to be allocated to a CPU core for computation. The ready queue has a queue header that contain a pointer to the first PCB, the PCB also contain a pointer to the next PCB and so on.
2. **Wait queue:** The wait queue stores previously executing PCBs which were deallocated. These PCBs are not terminating but waiting to be reallocted to a CPU core. For example a process requiring an I/O operation will be deallocated from the CPU due to the fact that I/O is a very slow process. these process are placed in the wait queue, once I/O is completed, it is reallocated.


![alt text](https://github.com/backendpapa/Operating-system-concept/blob/main/Process/queue.png?raw=true)

More reads: [CPU scheduling](https://en.wikipedia.org/wiki/Scheduling_(computing))


### CPU scheduling
A CPU scheduler selects a process from the ready queue and assign it to a CPU core. The schedular runs every 100miliseconds. 
I/O Bound process have short time staying in the CPU core.The scheduler deallocated while the I/O is taking place.
CPU bound process cant stay in the process for too long, they are deallocated and reallocated again to another CPU cores

### Context switch
When an interrupt occurs in a system, the CPU core needs to save the state and context of the current exexuting process to switch to a kernel routine or restore the state and context of another process to start executing on the CPU core. This is referred to as context switch. The context of a process is respresented by the PCB(Process Control Block) which contains information about the state, the register values.


## Operations on processes
A system must process a way to create and terminate a process.

### Process creation
When a process is executing, it can create other processes which are called **child processes**. The creating process is called the **parent process** and the child process could as well create other process thereby forming a process tree.
Every process has an identifier, an interger known as the PID or Process Identifier, it is a unique value assigned to each processes.

In Linux, the **systemd** always have a PID of 1, as it is the first process to be created, the systemd in return creates other processes such as the logind, the sshd and many more process.

![alt text](https://github.com/backendpapa/Operating-system-concept/blob/main/Process/create.png?raw=true)

When a child process is created, it requires certain resource like the CPU time, the memory files and I/O devices. The child process may require its resources direclty from the operating system or be restricted to obtaining from the subset of the parent resource. The latter is a better approach as it reduces the creation of too many child processes and prevents overloading the system.

Two execution possibilities exists when a child process is created
- The parent and the child process keep executing concurrently
- The parent process waits untils all child process have finished executing and have terminated.

Also two address space possibilities could occur
- The child process have the same code and program as the parent.
- The child program have entirely new program loaded into it.

When a new process is created via fork() method, it returns 0. here is an example below

```
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
    pid_t pid;
    /* fork a child process */
    pid = fork();
    if (pid < 0)
    { /* error occurred */
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    else if (pid == 0)
    { /* child process */
        execlp("/bin/ls", "ls", NULL);
    }
    else
    { /* parent process */
        /* parent will wait for the child to complete */
        wait(NULL);
        printf("Child Complete\n");
    }
}
```

![alt text](https://github.com/backendpapa/Operating-system-concept/blob/main/Process/creation.png?raw=true)

### Process termination
A process terminates when it is done executing all its statements, its ask the operating system to delete by calling exit() 
The deleting or terminating process may return a status code via wait() to the parent process. All resource allocated to the process such as virtual or physical memory, I/O buffers are deallocated and returned to the OS.

A process may terminate another process through an exit() system call, only the parent of that process can call the exit()

There are three (3) scenarios that can trigger the exit() call.
1. The child process has exceeded the allocated resources,
2. The child process has completed its executions
3. The parent process is exiting because some OS does not allow child processes to remain, they get terminated alongside (cascading termination).


The parent process might wait() for a child process exit() status code. these status code can be pased into the wait().
The parent has to call wait() to release the child process from the process table, if no wait() is called by the parent, the child process becomes a zombie process for a while.
A parent that terminated without invoking wait, leaves its child processes as orphan.
The init or systemd becomes the parent of such processes.

### Android process hierarchy
Due to limited memory challenge, mobile OS have a program termination rank as follow.
1. **Foreground process:** Most visible activity which the user is interacting with
2. **Background process:** Activities performed which the user is not aware of
3. **Visible process:** Visible activite which the user is not directly interacting with but performing activity the foreground is using
4. **Service:** Activities performed which the user is aware of such as streaming.
5. **Empty process:** Has no activity

Android eliminates process from hierarchy 5 to 1



## Interprocess communication (IPC)
A process can either be an independent process or an cooperating process.
An Process is independent if it does not share data with any other process while a cooperating process is a process that is affected if a data is changed by another process which means both process are sharing data

Reasons why cooperating processes exists could be  because:
1. They both need access to a particular information, for example the clipboard.
2. it needs to speed up it execution so the task or process is broken down to subtasks
3. as per program design, you want process divided into child processes or threads.

we can say Interprocess Communication is a mechanism that facilitate data exchange between two or more processes.

There are two models of IPC mechanism:
1. Shared memory
2. Message passing

In the shared memory, a region of memory for information sharing is created which is shared by the cooperating processes. Process can exchange information, read and write between each other

In message passing, its simple, information are exchanged by means of message toward each other.

![alt text](https://github.com/backendpapa/Operating-system-concept/blob/main/Process/ipc.png?raw=true)
