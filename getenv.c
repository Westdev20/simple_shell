#include "simple_shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments.
 *  Return: 1 on delete, 0 otherwise
 * @v: the string environment variable property
 */
int _unsetenv(info_t *info, char *v)
{
	list_t *n = info->env;
	size_t a = 0;
	char *p;

	if (!n || !v)
		return (0);
	while (n)
	{
		p = starts_with(n->str, v);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			n = info->env;
			continue;
		}
		n = n->next;
		a++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @v: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(info_t *info, char *v, char *value)
{
	char *buffer = NULL;
	list_t *n;
	char *p;

	if (!v || !value)
		return (0);

	buffer = malloc(_strlen(v) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buffer, v);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	n = info->env;
	while (n)
	{
		p = starts_with(n->str, v);
		if (p && *p == '=')
		{
			free(n->str);
			n->str = buffer;
			info->env_changed = 1;
			return (0);
		}
		n = n->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buffer);
	nfo->env_changed = 1;
	return (0);
}
