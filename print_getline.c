#include "shell.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * main - a program that prints "$ ",
 * wait for the user to enter a command,
 * prints it on the next line.
 */
int main(void)
{
	char *buffer, *prompt = "$ ";
	size_t b_size = 0;
	ssize_t bytes;
	pid_t wpid;
	int wstatus, len = strlen(buffer);
	struct stat buff;

	while (1)
	{
		/* Print the prompt sign '$ ' */
		write(STDOUT_FILENO, prompt, strlen(prompt));
		/* User to enter command */
		bytes = getline(&buffer, b_size, stdin);
		if (bytes == -1)
		{
			perror("Error in getting the user command");
			free(buffer);
			exit;
		}
		if (len > 0 && buffer[bytes - 1] == '\n')
			buffer[bytes - 1] = '\0'; /* remove the newline */
		wpid = fork;
		if (wpid == -1)
		{
			perror("Error");
			exit;
		}
		/* Parent process should wait for child process to finish */
		if (waitpid(wpid, &wstatus, 0) == -1)
		{
			perror("Error in waiting");
			exit;
		}
		/* Print the command entered by the user */
		char newline[] = "\n";
		write(STDOUT_FILENO, buffer, strlen(buffer));
		write(STDOUT_FILENO, newline, strlen(newline));
	}
}
