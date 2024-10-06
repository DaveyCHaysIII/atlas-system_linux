#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int i = 0;
	pid_t pid = getpid();
	char *name = "Holberton";

	while (i < 200)
	{
		printf("[%d] [PID: %d] %s\n", i, pid, name);
		sleep(1);
		i++;
	}
	return (0);
}
