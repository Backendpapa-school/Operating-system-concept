#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void)
{
    printf("Hello World\n");

    int pid = fork();
    printf("pid is %d",pid);
    if (pid > 0)
    {
        // Parent
        printf("Parent => My ID is %d\n", getpid());
         printf("this gets called before the wait %d\n",pid);
        printf("Parent => Child is created with ID %d\n", pid);
       
        int child_pid = wait(NULL);
        printf("Parent => Child process with ID %d is terminated\n", child_pid);
    }
    else if (pid == 0)
    {
        // Child process
        // Load a program
        printf("Child => Child is created with ID %d\n", getpid());
        // execlp("/bin/date", "date", NULL);
        //execlp("/bin/ls", "ls", "-la", NULL);
        char host[] = "google.com";
        execlp("/usr/bin/wget", "wget", host, NULL);
        exit(0);
    }
    return 0;
}