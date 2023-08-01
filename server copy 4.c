#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>

uint32_t	input_msg;
static int	bits;

static void	handler(int sig)
{

		if (sig == SIGUSR1)
		{
			// printf("SIGUSR1-signal recieved\n");
			// write(1, "1", 1);
			input_msg |= (1 << bits);
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
			printf("(handler) nothing happened\n");
			// exit(0);
		}
    // exit(0);
}


int main(void)
{
	const uint32_t	bitsize = 8;
	printf("Server runs ..\nPID:%d\n\n", getpid());

	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);

	while (1)
    {
		if (bits >= bitsize)
		{
			// write(1, "\n", 1);
			// printf("\nINCOMING CHAR:%c\n", (char)input_msg);
			if (input_msg == 4)
				printf("\n");
			write(1, &input_msg, 1);
			bits = 0;
			input_msg = 0;
			// sleep(1);
		}
		
    }
	return (0);
}
