#include <stdio.h>

/**
 * main - prints the environment
 * @argc: count the arguments
 * @argv: thw arguments
 * @env: the enivronment
 * Return: Always 0.
 */
int main(int argc, char **argv, char **env)
{
	unsigned int i;

	i = 0;
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
