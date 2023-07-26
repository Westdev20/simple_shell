#include "shell.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * main - a program that prints '$ '
 * Return: prompt
 */
int main(void)
{
	*prompt = "$ ";

	while (1)
	{
		/*Print the prompt sign '$ '*/
		write(STDOUT_FILENO, prompt, strlen(prompt));
	}
}
/**
 * input_buffer - buffers chained commands
 * @info: parameter struct
 * @buffer: address of buffer
 * @len: address of len var
 * if nothing left in the buffer, fill it
 * bfree((void **)info->cmd_buf);
 * remove trailing newline
 * if (_strchr(*buf, ';')) is this a command chain?
 * Return: bytes read(a)
 */
ssize_t input_buffer(info_t *info, char **buffer, size_t *len)
{
	ssize_t a = 0;
	size_t len_b = 0;

	if (!*len)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		a = getline(buffer, &len_b, stdin);
#else
		a = _getline(info, buffer, &len_b);
#endif
		if (a > 0)
		{
			if ((*buffer)[a - 1] == '\n')
			{
				(*buffer)[a - 1] = '\0';
				a--;
			}
			info->linecount_flag = 1;
			remove_comments(*buffer);
			build_history_list(info, *buffer, info->histcount++);
			{
				*len = a;
				info->cmd_buffer = buffer;
			}
		}
	}
	return (a);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 * Return: b
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buffer[READ_BUF_SIZE];
	static size_t i, len;
	size_t j;
	ssize_t a = 0, b = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		b = *length;
	if (i == len)
		i = len = 0;
	a = read_buf(info, buffer, &len);
	if (a == -1 || (a == 0 && len == 0))
		return (-1);

	c = _strchr(buffer + i, '\n');
	j = c ? 1 + (unsigned int)(c - buffer) : len;
	new_p = _realloc(p, b, b ? b + j : j + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (b)
		_strncat(new_p, buffer + i, j - i);
	else
		_strncpy(new_p, buffer + i, j - i + 1);

	b += j - i;
	i = j;
	p = new_p;

	if (length)
		*length = b;
	*ptr = p;
	return (s);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 * the ';' command chain buffer
 * get pointer for return
 * iterate to semicolon or end
 * if you have reached the end the buffer reset position
 * and length
 * pass back pointer to current command position
 * else pass back buffer from _getline()
 * and return length of buffer from _getline()
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buffer;
	static size_t i, j, len;
	ssize_t a = 0;
	char **buf_b = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buffer(info, &buffer, &len);
	if (a == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buffer + i;

		check_chain(info, buffer, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_b = p;
		return (_strlen(p));
	}
	*buf_b = buffer;
	return (a);
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buffer: the buffer
 * @i: size
 * Return: a
 */
ssize_t read_buf(info_t *info, char *buffer, size_t *i)
{
	ssize_t a = 0;

	if (*i)
		return (0);
	a = read(info->readfd, buffer, READ_BUF_SIZE);
	if (a >= 0)
		*i = a;
	return (a);
}
