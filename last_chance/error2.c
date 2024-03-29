#include "s_shell.h"

char *environ_error(char **agt);
char *error_1(char **agt);
char *error_2_exit(char **agt);
char *error_2_cd(char **agt);
char *error_2_syntax(char **agt);
/**
 * environ_error - Creates an error message for by_env errors.
 * @agt: An array of arguments passed to the cmd.
 *
 * Return: The error string.
 */
char *environ_error(char **agt)
{
	char *error, *hist_str;
	int len;

	hist_str = _attol(hist);
	if (!hist_str)
		return (NULL);

	agt--;
	len = _strlen(name) + _strlen(hist_str) + _strlen(agt[0]) + 45;
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
	_strcat(error, ": Unable to add/remove from environment\n");

	free(hist_str);
	return (error);
}

/**
 * error_1 - Creates an error message for by_alias errors.
 * @agt: An array of arguments passed to the cmd.
 *
 * Return: The error string.
 */
char *error_1(char **agt)
{
	char *error;
	int len;

	len = _strlen(name) + _strlen(agt[0]) + 13;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
		return (NULL);

	_strcpy(error, "alias: ");
	_strcat(error, agt[0]);
	_strcat(error, " not found\n");

	return (error);
}

/**
 * error_2_exit - Creates an error message for by_exit errors.
 * @agt: An array of arguments passed to the cmd.
 *
 * Return: The error string.
 */
char *error_2_exit(char **agt)
{
	char *error, *hist_str;
	int len;

	hist_str = _attol(hist);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(agt[0]) + 27;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": exit: Illegal number: ");
	_strcat(error, agt[0]);
	_strcat(error, "\n");

	free(hist_str);
	return (error);
}

/**
 * error_2_cd - Creates an error message for by_cd errors.
 * @agt: An array of arguments passed to the cmd.
 *
 * Return: The error string.
 */
char *error_2_cd(char **agt)
{
	char *error, *hist_str;
	int len;

	hist_str = _attol(hist);
	if (!hist_str)
		return (NULL);

	if (agt[0][0] == '-')
		agt[0][2] = '\0';
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
	if (agt[0][0] == '-')
		_strcat(error, ": cd: Illegal option ");
	else
		_strcat(error, ": cd: can't cd to ");
	_strcat(error, agt[0]);
	_strcat(error, "\n");

	free(hist_str);
	return (error);
}

/**
 * error_2_syntax - Creates an error message for syntax errors.
 * @agt: An array of arguments passed to the cmd.
 *
 * Return: The error string.
 */
char *error_2_syntax(char **agt)
{
	char *error, *hist_str;
	int len;

	hist_str = _attol(hist);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(agt[0]) + 33;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": Syntax error: \"");
	_strcat(error, agt[0]);
	_strcat(error, "\" unexpected\n");

	free(hist_str);
	return (error);
}
