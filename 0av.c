#include <stdio.h>
#include <stdlib.h>

/**
 * main - entry point
 * @ac: argument counter
 * @av: argument vector
 * Return: Always 0.
 *
 *
 *
 */

int main(int ac, char **av)
{
	int i = 0;

	while (av[i])
	{
		printf("%s ", av[i]);
		i++;
	}
	printf("\n");
	return (0);
}
