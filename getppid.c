#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t parent_pid = getppid();  // get the parent PID
    
    printf("Parent PID: %d\n", parent_pid);  // print the parent PID
    
    return 0;
}
