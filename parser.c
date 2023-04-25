#include "shell.h"

/**
 * exe_cmd - determines if a file is an executable command
 * @info: the info struct
 * @p: path to the file
 * Return: 1 if it is true, otherwise 0
 */
int exe_cmd(info_t *info, char *p)
{
	struct stat s;

	(void)info;
	if (!p || stat(p, &s))
	{
		return (0);
	}

	if (s.s_mode & S_IFREG)
	{
		return (1);
	}
}

/**
 * find_cmd_path - finds the command in the PATH string
 * @info: the info struct
 * @pstr: the PATH string
 * @cmd: the cmd to find
 * Return: full path of command if it is found else NULL
 */
char *find_cmd_path(info_t *info, char *pstr, char *cmd)
{
	int a = 0, current_position = 0;
	char *p;

	if (!pstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (exe_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!(!pstr[a] || pstr[a] == ':'))
		{
			_strcat(p, "/");
			_strcat(p, cmd);
		}
		else
		{
			p = duplicat_char(pstr, current_position, a);
			if (!*p)
				_strcat(p, cmd);
			if (exe_cmd(info, p))
				return (p);
			if (!pstr[a])
				break;
			current_position = a;
		}
		a++;
	}
	return (NULL);
}

/**
 * duplicate_char - duplicates the characters
 * @pstr: the PATH string
 * @begin: starting index
 * @stop: stopping index
 * Return: pointer to new buffer
 */
char *duplicate_char(char *pstr, int begin, int stop)
{
	static char buffer[1024];
	int a = 0, b = 0;

	for (b = 0, a = begin; a < stop; a++)
		if (pstr[a] != ':')
			buffer[b++] = pstr[a];
	buffer[b] = 0;
	return (buffer);
}
