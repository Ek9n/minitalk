#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

const char	*input;
int			pid_server;

static void	handler_key(int sig)
{
	static int	received = 0;

	if (sig == SIGQUIT)
	{
		kill(pid_server, SIGUSR2);
		printf("(handler_key) send: %s\n", input);
	}
	// else
	// {
	// 	//ft_putnbr_fd(received, 1);
	// 	printf("(handler_key) nothing happened\n");
	// 	exit(0);
	// }
}

void	send_msg()
{
	kill(pid_server, SIGUSR1);
	sleep(1);
	// wait();
}

int main(int argc, char **argv)
{
	if (argc == 2 || argc == 3)
	{
		pid_server = atoi(argv[1]);
		input = argv[2];
		if (argc == 3)
			signal(SIGQUIT, handler_key);
		while (1)
		{
			send_msg();
			
		}
	}
	else
		printf("client error\nno input\n");
	return (0);
}
