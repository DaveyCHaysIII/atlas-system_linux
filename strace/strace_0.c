#include "_strace.h"

/**
 * main - Entry point to our function
 * @argc: number of arguments
 * @argv: the argument vector
 *
 * return: 0 or 1
 */

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		perror("not enough args!");
		return (1);
	}

	pid_t child;
	child = fork();

	if (child == 0)
	{
		//child
		char *path = argv[1];
		char **child_args = &argv[1];
		char *env[] = {NULL};

		if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) == -1)
		{
			perror("ptrace child");
		}
		if (execve(path, child_args, env) == -1)
		{
			perror("execve");
		}
		return (1);
	}
	else
	{
		//parent
		int status;

		while (1)
		{
			if (waitpid(child, &status, 0) == -1)
			{
				perror("waitpid");
				return (1);
			}

			if (WIFEXITED(status))
			{
                		//printf("Exit status: %d\n", WEXITSTATUS(status));
                		break;
            		}
			else if (WIFSIGNALED(status))
			{
                		//printf("Terminated by signal: %d\n", WTERMSIG(status));
                		break;
            		}

			if (WIFSTOPPED(status))
			{
				struct user_regs_struct regs;
#ifdef __x86_64__
				if (ptrace(PTRACE_GETREGS, child, NULL, &regs) == -1)
				{
					perror("ptrace_regs");
					return (1);
				}
                		printf("%llu\n", regs.orig_rax);
#elif __i386__
				if (ptrace(PTRACE_GETREGS, child, NULL, &regs) == -1)
				{
					perror("ptrace_regs");
					return (1);
				}
                		printf("%lu\n", regs.orig_eax);
#else
#error unsupported architecture
#endif
			}

			if (ptrace(PTRACE_SYSCALL, child, NULL, NULL) == -1)
			{
				perror("ptrace parent");
				return(1);
			}
		}
	}
	return (0);
}
