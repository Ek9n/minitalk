#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static void	handler(int sig)
{
	// static int	received = 0;
	//ft_putnbr_fd(received, 1);

	// if (sig == SIGUSR2)
	// 	printf("SIGUSR2-signal recieved\n");
	// else
	// {
	// 	printf("(handler) nothing happened\n");
	// 	exit(0);
	// }


	if (sig == SIGUSR1)
		printf("SIGUSR1-signal recieved\n");
	else if (sig == SIGUSR2)
		printf("SIGUSR2-signal recieved\n");
	else
	{
		printf("(handler) nothing happened\n");
		exit(0);
	}
}


int main(void)
{
	printf("Server runs ..\nPID:%d\n", getpid());

	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	while (1);
	return (0);
}
