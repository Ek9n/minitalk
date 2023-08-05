#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include "../printf/ft_printf.h"
#include "../libft/libft.h"

static int	terminator;

int	ft_atoi(const char *nptr)
{
	int		i;
	int		sign;
	int		number;
	char	*str;

	str = (char *)nptr;
	i = 0;
	number = 0;
	sign = 1;
	if (str[i] == '\0')
		return (0);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		number = number * 10 + (str[i] - 48);
		i++;
	}
	return (number * sign);
}

void	send_signals(int pid, char character)
{
	int	timer;
	int	bit_index;

	timer = 0;
	bit_index = 0;
	while(bit_index < 8)
	{
		timer = 0;
		if (character & (0x01 << bit_index))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (terminator == 0)
		{
			if (timer == 100)
				printf("NO RESPONSE FROM SERVER :(\n)");
			timer++;
			usleep(100);
		}
		terminator = 0;
		bit_index++;
	}
}

void signal_confirm(int signum, siginfo_t *info, void *context)
{
	static int	bit = 0;
	
	terminator = 1;
	(void)context;
	(void)info;
	if (signum == SIGUSR2)
		bit++;
	else if (signum == SIGUSR1)
	{
		ft_printf("MSG SENT, %d bytes RECEIVED BACK FROM SERVER \n", bit/8);
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	action;
	static int	i = 0;

	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = signal_confirm;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	if (argc != 3 || ft_atoi(argv[1]) <= 0)
	{
		ft_printf("invalid argument(s) or format!\n");
		ft_printf("expected: ./client <serverPID> <\"MESSAGE\">\n");
		exit(1);
	}
	while (argv[2][i] != '\0')
	{
		send_signals(ft_atoi(argv[1]), argv[2][i]);
		i++;
	}
	send_signals(ft_atoi(argv[1]), '\0');
	while(1)
		pause();
	return (0);
}