#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>


int				pid_server;
const uint32_t		*input_msg;
// uint32_t		num_out;

static void	handler_key(int sig)
{
	if (sig == SIGQUIT)
	{
		kill(pid_server, SIGUSR2);
		printf("(handler_key) send: %s\n", input_msg);
	}
}

// void	send_char()
// {

// }

static void	send_msg(int pid, const uint32_t *str)
{
	uint32_t	bit;
	char		c;

	c = *str;
	while (*str++)
	{
		bit = -1;
		while (++bit < 8)
		{
			if (c >> bit & 1)
			{
				printf("1");
				kill(pid, SIGUSR1);
			}
			else
			{
				printf("0");
				kill(pid, SIGUSR2);
			}
			usleep(10);
		}
		// exit(0);
		c = *str;
	}

}

// 00101010



int main(int argc, char **argv)
{
	if (argc == 4)
		signal(SIGQUIT, handler_key);
	if (argc == 3)
	{
		pid_server = atoi(argv[1]);
		input_msg = argv[2];
		static int bits;
		static int i;
		printf("input_msg:%s\n", argv[2]);

		send_msg(pid_server, input_msg);
	}
	else
		printf("-client error-\nno valid input_msg\n");
	return (0);
}
