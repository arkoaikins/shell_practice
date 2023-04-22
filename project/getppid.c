#include <stdio.h>
#include <unistd.h>

/**
 * main - PID
 *
 * Return: Always 0.
 */

int main() {
    printf("Parent process ID: %d\n", getppid());
    return 0;
}
