#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>

uint32_t	num_in;
static int	bits;

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

	// if ((sig == SIGUSR1))
	// {
		if (sig == SIGUSR1)
		{
			// printf("SIGUSR1-signal recieved\n");
			write(1, "1", 1);
			num_in |= (1 << bits);
			bits++;
		}
		else if (sig == SIGUSR2)
		{
			// printf("SIGUSR2-signal recieved\n");
			write(1, "0", 1);
			// num_in |= (1 << bits);
			// printf("Before - num_in:%d\n", num_in);
			// printf("After - num_in:%d\n\n", num_in);
			bits++;
		}
		else
		{
			printf("(handler) nothing happened\n");
			// exit(0);
			// printf("else num_in:%d\n", num_in);
			// printf("sizeof(uint32_t):%lu\n", sizeof(uint32_t));
		}
	// }

    // printf("num_in:%d\n\n", num_in);
    // exit(0);
}


int main(void)
{
	printf("Server runs ..\nPID:%d\n", getpid());

	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	// while (bits--)
	while (1)
    {
		if (bits >= 8)
		{
			printf("\nINCOMING CHAR:%c\n", (char)num_in);
			bits = 0;
			sleep(5);
		}
        // printf("...............\nnum_in to decimal:%d\n", num_in);
    }
	return (0);
}
