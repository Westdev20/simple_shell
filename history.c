#include "simple_shell.h"

/**
 * get_history - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history(info_t *info)
{
	char *buffer, *d;

	d = _getenv(info, "HOME=");
	if (!d)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, d);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * write_history_file - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success or else -1
 */
int write_history_file(info_t *info)
{
	ssize_t fd;
	char *fname = get_history(info);
	list_t *node = NULL;

	if (!fname)
		return (-1);

	fd = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fname);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success else 0
 */
int read_history(info_t *info)
{
	int a, last = 0, lcount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buffer = NULL, *fname = get_history(info);

	if (!fname)
		return (0);

	fd = open(fname, O_RDONLY);
	free(fname);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fsize + 1));
	if (!buffer)
		return (0);
	rdlen = read(fd, buffer, fsize);
	buffer[fsize] = 0;
	if (rdlen <= 0)
		return (free(buffer), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buffer[a] == '\n')
		{
			buffer[a] = 0;
			build_history_list(info, buffer + last, lcount++);
			last = a + 1;
		}
	if (last != a)
		build_history_list(info, buffer + last, lcount++);
	free(buffer);
	info->histcount = lcount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buffer: the buffer
 * @lcount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history(info_t *info, char *buffer, int lcount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buffer, lcount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int a = 0;

	while (node)
	{
		node->num = a++;
		node = node->next;
	}
	return (info->histcount = a);
}
