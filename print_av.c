#include <stdio.h>

/**
 * main - Print all the arguments, without using ac.
 * @argc: count arguments
 * @argv: Arguments
 * Return: 0
 */
int main(int argc, char *argv[])
{
	int count = 0;

	if (argc > 0)
	{
		while (count < argc)
		{
			printf("%s\n", argv[count]);
			count++;
		}
	}
	return (0);
}
