#include "simple_shell.h"

/**
 * test_chain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buffer: the char buffer
 * @pos: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int test_chain(info_t *info, char *buffer, size_t *pos)
{
	size_t j = *p;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		info->cmd_buffer_type = CMD_OR;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		info->cmd_buffer_type = CMD_AND;
	}
	else if (buffer[j] == ';')
	{
		buffer[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	*pos = j;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buffer: the char buffer
 * @pos: address of current position in buffer
 * @i: starting position in buffer
 * @l: length of buffer
 * Return: Void
 */
void check_chain(info_t *info, char *buffer, size_t *pos, size_t i, size_t l)
{
	size_t j = *pos;

	if (info->cmd_buffer_type == CMD_AND)
	{
		if (info->status)
		{
			buffer[i] = 0;
			a = l;
		}
	}
	if (info->cmd_buffer_type == CMD_OR)
	{
		if (!info->status)
		{
			buffer[i] = 0;
			a = l;
		}
	}

	*pos = a;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 * Return: 1 if it is replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int a;
	list_t *n;
	char *p;

	for (a = 0; a < 10; a++)
	{
		n = n_starts_with(info->alias, info->argv[0], '=');
		if (!n)
			return (0);
		free(info->argv[0]);
		p = _strchr(n->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_var - replaces var in the (tokenized) string
 * @info: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int replace_var(info_t *info)
{
	int i = 0;
	list_t *n;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;
		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		n = n_starts_with(info->env, &info->argv[i][1], '=');
		if (n)
		{
			replace_string(&(info->argv[i]),
					_strdup(_strchr(n->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @previous: address of old string
 * @new: address of new string
 * Return: 1 if success, 0 otherwise
 */
int replace_string(char **previous, char *new)
{
	free(*previous);
	*previous = new;
	return (1);
}
