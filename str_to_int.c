#include "shell.h"

/**
 * alpha_char - checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int alpha_char(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - Convert a string to an integer
 * @s: char array string
 * Description: Number in the string can be preceded by an infinite
 * number of characters
 * All -/+ signs before the number should be in consideration
 * If there are no numbers in the string, return 0
 * No need to check for overflow
 * Not allowed to hard-code special values
 * Return: first integer found in the string
 */
int _atoi(char *s)
{
	int a = 0;
	unsigned int b = 0;
	int c = 1;
	int d = 0;

	while (s[a])
	{
		if (s[a] == 45)
		{
			c *= -1;
		}
		while (s[a] >= 48 && s[a] <= 57)
		{
			d = 1;
			b = (b * 10) + (s[a] - '0');
			a++;
		}
		if (d == 1)
		{
			break;
		}
		a++;
	}
	b *= c;
	return (b);
}
