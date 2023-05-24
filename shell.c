#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>


int main(int ac, char *av[], char *ev[])
{
	char *cmd = NULL;
	size_t size = 0;
	pid_t fid;
	int count = 0;
	ssize_t len;
	int i;

	while (1)
	{
		i = 0;

		write(STDOUT_FILENO, "$ ", 2);
		len = getline(&cmd, &size, stdin);

		if (len == -1)
		{
			if (cmd != NULL)
				free(cmd);
			write(STDOUT_FILENO, "\nExiting...\n", 12);
			break;
		}
		cmd[len - 1] = '\0';

		fid = fork();
		count++;
		if (fid == -1)
		{
			perror(av[0]);
			return (1);
		}
		if (fid == 0)
		{
			if (execve(cmd, av, ev) == -1)
			{
				perror(av[0]);
			}
		}
		else
			wait(NULL);

		free(cmd);
		cmd = NULL;
	}
	return (0);
}
