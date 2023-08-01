#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>


int					pid_server;
const uint32_t		*input_msg;
const uint32_t		bitsize = 8;
// uint32_t		num_out;

static void	handler_key(int sig)
{
	if (sig == SIGQUIT)
	{
		kill(pid_server, SIGUSR2);
		// printf("(handler_key) send: %s\n", input_msg);
	}
}

// void	send_char()
// {

// }

static void	send_msg(int pid, const uint32_t *msg)
{
	uint32_t	bit;
	char		c;
	int			bitsize_msg = strlen((char *)msg) * bitsize;
	int			bytesize_msg = strlen((char *)msg);

	char *cast_msg = (char *)msg;

	printf("bitsize_msg:%d\n", bitsize_msg);

	c = *cast_msg;
	while (*cast_msg++ && bytesize_msg)
	{
		bit = -1;
		while (++bit < bitsize)
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
		c = *cast_msg;
		bytesize_msg--;
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
		input_msg = (void *)argv[2];
		static int bits;
		static int i;
		printf("input_msg:%s\n", argv[2]);

		send_msg(pid_server, input_msg);
	}
	else
		printf("-client error-\nno valid input_msg\n");
	return (0);
}