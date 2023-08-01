#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>

uint32_t    int_char;
    static uint8_t cnt_bit;


static void	handler(int sig)
{
    static int bits;

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
    {
		printf("SIGUSR1-signal recieved\n");
    }
	else if (sig == SIGUSR2)
    {
        printf("SIGUSR2-signal recieved\n");
        printf("Before - Cnt_bit:%d\n", cnt_bit);
        cnt_bit |= (1 << bits);
        printf("After - Cnt_bit:%d\n\n", cnt_bit);
        bits++;
    }
	else
	{
		printf("(handler) nothing happened\n");
		// exit(0);
        // printf("else Cnt_bit:%d\n", cnt_bit);
        // printf("sizeof(uint8_t):%lu\n", sizeof(uint8_t));

	}
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
        // printf("...............\ncnt_bit to decimal:%d\n", cnt_bit);
    }
	return (0);
}
