#include "s_shell.h"

char *error_126(char **agt);
char *error_127(char **agt);

/**
 * error_126 - Creates an error message for permission denied failures.
 * @agt: An array of arguments passed to the cmd.
 *
 * Return: The error string.
 */
char *error_126(char **agt)
{
	char *error, *hist_str;
	int len;

	hist_str = _attol(hist);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(agt[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": ");
	_strcat(error, agt[0]);
	_strcat(error, ": Permission denied\n");

	free(hist_str);
	return (error);
}

/**
 * error_127 - Creates an error message for cmd not found failures.
 * @agt: An array of arguments passed to the cmd.
 *
 * Return: The error string.
 */
char *error_127(char **agt)
{
	char *error, *hist_str;
	int len;

	hist_str = _attol(hist);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(agt[0]) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": ");
	_strcat(error, agt[0]);
	_strcat(error, ": not found\n");

	free(hist_str);
	return (error);
}
