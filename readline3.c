#include <stdio.h>
#include <stdlib.h>

/**
 * main - Entry point
 *
 * A program that prints "$ ",
 * wait for the user to enter a command,
 * prints it on the next line.
 * Has EOF with malloc: succes
 *
 * Return: Always 0.
 */

int main(void)
{
	char *buffer = NULL;
	size_t len = 0;

	if (buffer == NULL)
	{
		perror("malloc");
		return (1);
	}

	while (1)
	{
		printf("$ ");
		ssize_t ncom = getline(&buffer, &len, stdin);
		if (ncom == -1 && feof(stdin))
			break;
		if (ncom == -1)
		{
			perror("getline");
			break;
		}
		printf("%s", buffer);
	}

	free(buffer);
	return (0);
}
