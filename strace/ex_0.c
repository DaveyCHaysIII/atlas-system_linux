#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

int main(int argc, char **argv, char **env)
{
	pid_t child;
	child = fork();

	if (child == 0)
	{
		//child process
		ptrace(PTRACE_TRACEME, 0, NULL, NULL);
		execve(argv[1], argv, env);
	}
	else
	{
		//parent process
		int status;
		while(1)
		{
			waitpid(child, &status, 0);
			if (WIFEXITED(status))
			{
				break;
			}
			if (ptrace(PTRACE_SINGLESTEP, child, NULL, NULL) == -1)
			{
				 //err
				return (1);
			}
			printf("single step\n");
		}
	}
	return (0);
}
