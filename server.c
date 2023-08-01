#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>

uint32_t	incoming_type;
// size_t	incoming_type;
static int	bits;

static void	handler(int sig)
{

		if (sig == SIGUSR1)
		{
			// printf("SIGUSR1-signal recieved\n");
			// write(1, "1", 1);
			incoming_type |= (1 << bits);
			bits++;
		}
		else if (sig == SIGUSR2)
		{
			// printf("SIGUSR2-signal recieved\n");
			// write(1, "0", 1);
			bits++;
		}
		else
		{
			printf("(handler) something happened\n");
			exit(0);
		}
}


int main(void)
{
	const uint32_t	bitsize = 8;
	printf("Server runs ..\nPID:%d\n\n", getpid());

	incoming_type = 0;
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	while (1)
    {
		if (bits >= bitsize)
		{

			// write(1, "\n", 1);
			// printf("\nINCOMING CHAR:%c\n", (char)incoming_type);
			if (incoming_type == 4)
				printf("\n");
			write(1, &incoming_type, 1);
			bits = 0;
			incoming_type = 0;
			// sleep(1);
		}
		
    }
	return (0);
}
