#include <stdio.h>
#include <unistd.h>

/**
 * main - Write a program that prints the PID of the parent process.
 * Run your program several times within the same shell.
 * It should be the same
 *
 * Return: Always 0.
 */
int main(void)
{
	pid_t my_pid, the_ppid;

	my_pid = getpid();
	the_ppid = getppid();
	printf("my_pid = %d\nparent pid = %u\n", my_pid, the_ppid);
	return (0);
}
