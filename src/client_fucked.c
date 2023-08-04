/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 02:27:10 by hstein            #+#    #+#             */
/*   Updated: 2023/08/04 02:31:51 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

int				g_pid_server;
uint32_t		*g_msg;
const uint32_t	g_bitsize = 8;
static bool		server_rdy;

void	send_char(int pid, uint32_t g_bitsize, char c)
{
	uint32_t	bit;
	// printf("char in sendchar:%c\n", c);
	bit = -1;
	while (++bit < g_bitsize)
	{
		if (c >> bit & 1)
		{
			// write(1, "1", 1);
			kill(pid, SIGUSR1);
		}
		else
		{
			// write(1, "0", 1);
			kill(pid, SIGUSR2);
		}
		usleep(1000);
		// sleep(1);
	}
}

static void	send_msg(int pid, const uint32_t *msg)
{
	char		c;
	int			g_bitsize_msg;
	int			bytesize_msg;
	char		*cast_msg;

	g_bitsize_msg = ft_strlen((char *)msg) * g_bitsize;
	bytesize_msg = ft_strlen((char *)msg);
	cast_msg = (char *)msg;
	printf("\nBits sent: %d\n", g_bitsize_msg);
	c = *cast_msg;
	while (*cast_msg++ && bytesize_msg)
	{
		send_char(pid, g_bitsize, c);
		c = *cast_msg;
		bytesize_msg--;
	}
}

static void	send_start_msg(int pid)
{
	char	c;

	write(1, "\n#send - asking for permission (ACK)\n", \
		ft_strlen("\n#send - asking for permission (ACK)\n"));
	c = 6; //ACK Ascii
	send_char(pid, g_bitsize, c);
	// sleep(1);
	usleep(1000);
}

// client schickt startmsg -> client wartet bis server sigurs1 sendet
static void	handler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;

	if (sig == SIGUSR1)
	{
		ft_printf("\n#server send ok\n");
		server_rdy = true;
	}
	else if (sig == SIGUSR2)
	{
		ft_printf("\n#server recieved msg\n");
		server_rdy = true;
		exit(0);
	}
	else
	{
		ft_printf("(handler) something happened\n");
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	s_sigaction;

	if (argc == 3)
	{
		printf("client pid:%d\n", getpid());
		g_pid_server = atoi(argv[1]);
		g_msg = (void *)argv[2];
		s_sigaction.sa_sigaction = handler;
		s_sigaction.sa_flags = SA_SIGINFO;
		sigaction(SIGUSR1, &s_sigaction, NULL);
		while (!server_rdy)
			send_start_msg(g_pid_server);
		write(1, "#send - g_msg:", ft_strlen("#send - g_msg:"));
		write(1, argv[2], ft_strlen(argv[2]));
		write(1, "\n...", 4);
		send_msg(g_pid_server, g_msg);
		write(1, "\n#send - end of transmission (EOT)", \
			ft_strlen("\n#send - end of transmission (EOT)"));
		sigaction(SIGUSR2, &s_sigaction, NULL);
		*g_msg = 4;
		while (1)
			send_msg(g_pid_server, g_msg);
		pause();
		server_rdy = false;
	}
	else
	{
		write(1, "-client error-\nno valid g_msg\n", \
			ft_strlen("-client error-\nno valid g_msg\n"));
	}
	// while(1);
	return (0);
}
