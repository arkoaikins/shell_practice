#include "s_shell.h"

char *get_agt(char *line, int *impret);
int call_agt(char **agt, char **top, int *impret);
int run_agt(char **agt, char **top, int *impret);
int handle_agt(int *impret);
int check_agt(char **agt);

/**
 * get_agt - Gets a cmd from standard input.
 * @line: A buffer to store the cmd.
 * @impret: The return value of the last performd cmd.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the stored cmd.
 */
char *get_agt(char *line, int *impret)
{
	size_t n = 0;
	ssize_t read;
	char *prompt = "$ ";

	if (line)
		free(line);

	read = line_gets(&line, &n, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_agt(line, impret));
	}

	line[read - 1] = '\0';
	_replacer(&line, impret);
	handle_line(&line, read);

	return (line);
}

/**
 * call_agt - Partitions operators from cmds and calls them.
 * @agt: An array of arguments.
 * @top: A double pointer to the beginning of agt.
 * @impret: The return value of the parent process' last performd cmd.
 *
 * Return: The return value of the last performd cmd.
 */
int call_agt(char **agt, char **top, int *impret)
{
	int ret, index;

	if (!agt[0])
		return (*impret);
	for (index = 0; agt[index]; index++)
	{
		if (_strncmp(agt[index], "||", 2) == 0)
		{
			free(agt[index]);
			agt[index] = NULL;
			agt = change_aliases(agt);
			ret = run_agt(agt, top, impret);
			if (*impret != 0)
			{
				agt = &agt[++index];
				index = 0;
			}
			else
			{
				for (index++; agt[index]; index++)
					free(agt[index]);
				return (ret);
			}
		}
		else if (_strncmp(agt[index], "&&", 2) == 0)
		{
			free(agt[index]);
			agt[index] = NULL;
			agt = change_aliases(agt);
			ret = run_agt(agt, top, impret);
			if (*impret == 0)
			{
				agt = &agt[++index];
				index = 0;
			}
			else
			{
				for (index++; agt[index]; index++)
					free(agt[index]);
				return (ret);
			}
		}
	}
	agt = change_aliases(agt);
	ret = run_agt(agt, top, impret);
	return (ret);
}

/**
 * run_agt - Calls the execution of a cmd.
 * @agt: An array of arguments.
 * @top: A double pointer to the beginning of agt.
 * @impret: The return value of the parent process' last performd cmd.
 *
 * Return: The return value of the last performd cmd.
 */
int run_agt(char **agt, char **top, int *impret)
{
	int ret, i;
	int (*builtin)(char **agt, char **top);

	builtin = get_builtin(agt[0]);

	if (builtin)
	{
		ret = builtin(agt + 1, top);
		if (ret != EXIT)
			*impret = ret;
	}
	else
	{
		*impret = perform(agt, top);
		ret = *impret;
	}

	hist++;

	for (i = 0; agt[i]; i++)
		free(agt[i]);

	return (ret);
}

/**
 * handle_agt - Gets, calls, and runs the execution of a cmd.
 * @impret: The return value of the parent process' last performd cmd.
 *
 * Return: If an end-of-file is read - END_OF_FILE (-2).
 *         If the input cannot be tokenized - -1.
 *         O/w - The exit value of the last performd cmd.
 */
int handle_agt(int *impret)
{
	int ret = 0, index;
	char **agt, *line = NULL, **top;

	line = get_agt(line, impret);
	if (!line)
		return (END_OF_FILE);

	agt = strtoken(line, " ");
	free(line);
	if (!agt)
		return (ret);
	if (check_agt(agt) != 0)
	{
		*impret = 2;
		free_agt(agt, agt);
		return (*impret);
	}
	top = agt;

	for (index = 0; agt[index]; index++)
	{
		if (_strncmp(agt[index], ";", 1) == 0)
		{
			free(agt[index]);
			agt[index] = NULL;
			ret = call_agt(agt, top, impret);
			agt = &agt[++index];
			index = 0;
		}
	}
	if (agt)
		ret = call_agt(agt, top, impret);

	free(top);
	return (ret);
}

/**
 * check_agt - Checks if there are any leading ';', ';;', '&&', or '||'.
 * @agt: 2D pointer to tokenized cmds and arguments.
 *
 * Return: If a ';', '&&', or '||' is placed at an invalid position - 2.
 *   Otherwise - 0.
 */
int check_agt(char **agt)
{
	size_t i;
	char *cur, *nex;

	for (i = 0; agt[i]; i++)
	{
		cur = agt[i];
		if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
		{
			if (i == 0 || cur[1] == ';')
				return (do_error(&agt[i], 2));
			nex = agt[i + 1];
			if (nex && (nex[0] == ';' || nex[0] == '&' || nex[0] == '|'))
				return (do_error(&agt[i + 1], 2));
		}
	}
	return (0);
}
