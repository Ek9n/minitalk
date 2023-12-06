/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 02:27:10 by hstein            #+#    #+#             */
/*   Updated: 2023/08/05 22:43:56 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

static bool	g_confirmed;

void	send_char(int pid, uint32_t bitsize, char c)
{
	uint32_t	bit;

	bit = -1;
	while (++bit < bitsize)
	{
		g_confirmed = false;
		while (!g_confirmed)
		{
			if (c >> bit & 1)
			{
				if (kill(pid, SIGUSR1) == -1)
					error_exit();
			}
			else
			{
				if (kill(pid, SIGUSR2) == -1)
					error_exit();
			}
			usleep(5);
		}
	}
}

static void	send_msg(int pid, const uint32_t *msg, uint32_t bitsize)
{
	char		c;
	int			bitsize_msg;
	int			bytesize_msg;
	char		*cast_msg;

	bitsize_msg = ft_strlen((char *)msg) * bitsize;
	bytesize_msg = ft_strlen((char *)msg);
	cast_msg = (char *)msg;
	c = *cast_msg;
	while (*cast_msg++ && bytesize_msg)
	{
		send_char(pid, bitsize, c);
		c = *cast_msg;
		bytesize_msg--;
	}
	ft_printf("\nBits sent: %d\n", bitsize_msg);
}

void	send_endofmsg(struct sigaction s_sigaction, \
			int pid_server, uint32_t bitsize)
{
	uint32_t	msg;

	msg = 4;
	sigaction(SIGUSR2, &s_sigaction, NULL);
	send_msg(pid_server, &msg, bitsize);
	while (!g_confirmed)
	{
	}
}

static void	handler(int sig, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	if (sig == SIGUSR1)
	{
		usleep(5);
		g_confirmed = true;
	}
	else if (sig == SIGUSR2)
	{
		ft_printf("\n#MSG confirmed by server\n");
		g_confirmed = true;
	}
	else
	{
		ft_printf("\n(handler) something happened\n");
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	s_sigaction;
	int					pid_server;
	uint32_t			*msg;
	uint32_t			bitsize;

	bitsize = 8;
	if (argc == 3)
	{
		s_sigaction.sa_sigaction = handler;
		s_sigaction.sa_flags = SA_SIGINFO;
		pid_server = atoi(argv[1]);
		msg = (void *)argv[2];
		ft_printf("#sending - msg\n...");
		sigaction(SIGUSR1, &s_sigaction, NULL);
		send_msg(pid_server, msg, bitsize);
		ft_printf("\n#send - end of transmission (EOT)");
		sigaction(SIGUSR2, &s_sigaction, NULL);
		send_endofmsg(s_sigaction, pid_server, bitsize);
	}
	else
		ft_printf("-client error-\nno valid msg\n");
	return (0);
}
