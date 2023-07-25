#include <stdio.h>
#include <unistd.h>

int main(void)
{
	long maxpid = sysconf(_SC_CHILD_MAX);

	printf("The maximum process ID value is: %ld\n", maxpid);
	return (0);
}
