#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include "../printf/ft_printf.h"
#include "../libft/libft.h"

void signal_handler(int signum, siginfo_t *info, void *context)
{
	static int	bit = 0;
	static int	pid = 0;
	static char byte = 0;
	
	(void)context;
	pid = info->si_pid;
	if (signum == SIGUSR1)
		byte |= (0x01 << bit);
	bit++;
	if (bit == 8)
	{
		bit = 0;
		if(!byte)
		{
			kill (pid, SIGUSR1);
			pid = 0;
			ft_printf("\n");
			return;
		}
		ft_printf("%c", byte);
		byte = 0;
	}
	kill(pid, SIGUSR2);
}

int main(void)
{
	int pid;
	struct sigaction	action;

	pid = getpid();
	ft_printf("Welcome!\nServer's PID: %d\n", pid);
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = signal_handler;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while(1)
		pause();
	return (0);
}