#include "_strace.h"

/**
 * main - Entry point to our function
 * @argc: number of arguments
 * @argv: the argument vector
 *
 * Return: 0 or 1
 */


int main(int argc, char **argv, char **env)
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
		ptrace(PTRACE_TRACEME, 0, NULL, NULL);
		execve(argv[1], &argv[1], env);
	}
	else
	{
		parent_process(child);
	}
	return (0);
}

/**
 * parent_process - handles the parent process
 * @child: the child PID
 *
 * Return: 0 or 1
 */

int parent_process(pid_t child)
{
	int status, entry = 0;
	struct user_regs_struct regs;
	syscall_t const *callinfo;

	while (1)
	{
		if (waitpid(child, &status, 0) == -1)
			return (1);

		if (WIFEXITED(status))
			break;

		if (ptrace(PTRACE_GETREGS, child, NULL, &regs) == -1)
			perror("ptrace_regs"), exit(1);

		if (entry == 0 || entry % 2 != 0)
		{
			callinfo = &syscalls_64_g[regs.orig_rax];
			fprintf(stderr, "%s", callinfo->name);
			print_params(&regs, callinfo);
			if (regs.orig_rax == 59)
				fprintf(stderr, "= 0\n");
			else if (regs.orig_rax == 231)
				fprintf(stderr, "= ?\n");
		}
		else
			fprintf(stderr, "= %#llx\n", regs.rax);

		if (ptrace(PTRACE_SYSCALL, child, NULL, NULL) == -1)
			return (1);
		entry++;
		fflush(NULL);
	}
	return (0);
}

void print_params(struct user_regs_struct *regs, syscall_t const *callinfo)
{
	size_t i;

	fprintf(stderr, "(");
	if (callinfo->nb_params == 0)
		fprintf(stderr, "0");
	else
	{
		for (i = 0; i < callinfo->nb_params; i++)
		{
			switch(i)
			{
				case(0):
					fprintf(stderr, "%#llx", regs->rdi); break;
				case(1):
					fprintf(stderr, "%#llx", regs->rsi); break;
				case(2):
					fprintf(stderr, "%#llx", regs->rdx); break;
				case(3):
					fprintf(stderr, "%#llx", regs->r10); break;
				case(4):
					fprintf(stderr, "%#llx", regs->r8); break;
				case(5):
					fprintf(stderr, "%#llx", regs->r9); break;
				default:
					printf("?????");
			}
			if (i != callinfo->nb_params - 1)
				fprintf(stderr, ", ");
		}
	}
	fprintf(stderr, ") ");
}
