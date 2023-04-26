#include "s_shell.h"

int cant_open(char *file_path);
int prog_commd(char *file_path, int *impret);

/**
 * cant_open - If the file doesn't exist or lacks proper permissions, print
 * a cant open error.
 * @file_path: Path to the supposed file.
 *
 * Return: 127.
 */

int cant_open(char *file_path)
{
	char *error, *hist_str;
	int len;

	hist_str = _attol(hist);
	if (!hist_str)
		return (127);

	len = _strlen(name) + _strlen(hist_str) + _strlen(file_path) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (127);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": Can't open ");
	_strcat(error, file_path);
	_strcat(error, "\n");

	free(hist_str);
	write(STDERR_FILENO, error, len);
	free(error);
	return (127);
}

/**
 * prog_commd - Takes a file and attempts to run the cmds stored
 * within.
 * @file_path: Path to the file.
 * @impret: Return value of the last performd cmd.
 *
 * Return: If file couldn't be opened - 127.
 *   If malloc fails - -1.
 *   Otherwise the return value of the last cmd ran.
 */
int prog_commd(char *file_path, int *impret)
{
	ssize_t file, b_read, i;
	unsigned int line_size = 0;
	unsigned int size1 = 120;
	char *line, **agt, **top;
	char buffer[120];
	int ret;

	hist = 0;
	file = open(file_path, O_RDONLY);
	if (file == -1)
	{
		*impret = cant_open(file_path);
		return (*impret);
	}
	line = malloc(sizeof(char) * size1);
	if (!line)
		return (-1);
	do {
		b_read = read(file, buffer, 119);
		if (b_read == 0 && line_size == 0)
			return (*impret);
		buffer[b_read] = '\0';
		line_size += b_read;
		line = re_alloc(line, size1, line_size);
		_strcat(line, buffer);
		size1 = line_size;
	} while (b_read);
	for (i = 0; line[i] == '\n'; i++)
		line[i] = ' ';
	for (; i < line_size; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = ';';
			for (i += 1; i < line_size && line[i] == '\n'; i++)
				line[i] = ' ';
		}
	}
	_replacer(&line, impret);
	handle_line(&line, line_size);
	agt = strtoken(line, " ");
	free(line);
	if (!agt)
		return (0);
	if (check_agt(agt) != 0)
	{
		*impret = 2;
		free_agt(agt, agt);
		return (*impret);
	}
	top = agt;

	for (i = 0; agt[i]; i++)
	{
		if (_strncmp(agt[i], ";", 1) == 0)
		{
			free(agt[i]);
			agt[i] = NULL;
			ret = call_agt(agt, top, impret);
			agt = &agt[++i];
			i = 0;
		}
	}

	ret = call_agt(agt, top, impret);

	free(top);
	return (ret);
}
