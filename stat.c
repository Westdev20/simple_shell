#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * main - status of the file
 * @argv: the arguments
 * @argc: count of the arguments
 * Return: Always 0.
 */
int main(int argc, char **argv)
{
	unsigned int i;
	struct stat st;

	if (argc < 2)
	{
		printf("Usage: %s path_to_file ...\n", argv[0]);
		return (1);
	}
	while (argv[i])
	{
		printf("%s:", argv[i]);
		if (stat(argv[i], &st) == 0)
			printf(" FOUND\n");
		else
		{
			printf(" NOT FOUND\n");
		}
		i++;
	}
	return (0);
}
