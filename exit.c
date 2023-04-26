#include "simple_shell.h"

/**
 * *_strncpy - coppy a string
 * @dest: destination value
 * @src: source value
 * @n: input value
 * Return: dest
 */
char *_strncpy(char *dest, char *src, int n)
{
	int j;

	j = 0;
	while (j < n && src[j] != '\0')
	{
		dest[j] = src[j];
		j++;
	}
	while (j < n)
	{
		dest[j] = '\0';
		j++;
	}
	return (dest);
}

/**
 * *_strncat - This function appends the src string to the dest string
 * it will use at most n bytes from src; and
 * src does not need to be null-terminated if it contains n or more bytes
 * @dest: destination value
 * @src: source value
 * @n: input value
 * Return: pointer to the resulting string dest
 */
char *_strncat(char *dest, char *src, int n)
{
	int i;
	int j;

	i = 0;
	while (dest[i] != 0)
	{
		i++;
	}
	j = 0;
	while (j < n && src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * *_strchr - function that locates a character in a string
 * @s: character of the string
 * @c: character
 * in the string s, or NULL if the character is not found
 * Return: pointer to the first occurrence of the character c
 */
char *_strchr(char *s, char c)
{
	int a = 0;

	for (; s[a] >= '\0'; a++)
	{
		if (s[a] == c)
		{
			return (&s[a]);
		}
	}
	return (0);
}
