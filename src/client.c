// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   client.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/08/02 02:27:10 by hstein            #+#    #+#             */
// /*   Updated: 2023/08/02 23:07:37 by hstein           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../minitalk.h"

// int				g_pid_server;
// const uint32_t	g_bitsize = 8;

// void	send_char(int pid, uint32_t g_bitsize, char c)
// {
// 	uint32_t	bit;

// 	bit = -1;
// 	while (++bit < g_bitsize)
// 	{
// 		if (c >> bit & 1)
// 		{
// 			write(1, "1", 1);
// 			kill(pid, SIGUSR1);
// 		}
// 		else
// 		{
// 			write(1, "0", 1);
// 			kill(pid, SIGUSR2);
// 		}
// 		usleep(100);
// 	}
// }

// static void	send_msg(int pid, const uint32_t *msg)
// {
// 	char		c;
// 	int			g_bitsize_msg;
// 	int			bytesize_msg;
// 	char		*cast_msg;

// 	g_bitsize_msg = ft_strlen((char *)msg) * g_bitsize;
// 	bytesize_msg = ft_strlen((char *)msg);
// 	cast_msg = (char *)msg;
// 	printf("\nBits sent: %d\n", g_bitsize_msg);
// 	c = *cast_msg;
// 	while (*cast_msg++ && bytesize_msg)
// 	{
// 		send_char(pid, g_bitsize, c);
// 		c = *cast_msg;
// 		bytesize_msg--;
// 	}
// }

// void	send_stx()
// {
// 	uint32_t	msg;

// 	msg = 2;
// 	write(1, "\n#send - start of text (STX)", \
// 		ft_strlen("\n#send - start of text (STX)"));
// 	send_msg(g_pid_server, &msg);
// }

// void	send_eot()
// {
// 	uint32_t	msg;

// 	msg = 4;
// 	write(1, "\n#send - end of transmission (EOT)", \
// 		ft_strlen("\n#send - end of transmission (EOT)"));
// 	send_msg(g_pid_server, &msg);
// }

// int	main(int argc, char **argv)
// {
// 	if (argc == 3)
// 	{
// 		uint32_t		*g_msg;

// 		g_pid_server = atoi(argv[1]);
// 		send_stx();
// 		g_msg = (void *)argv[2];
// 		write(1, "\n#send - g_msg:", ft_strlen("\n#send - g_msg:"));
// 		write(1, argv[2], ft_strlen(argv[2]));
// 		send_msg(g_pid_server, g_msg);
// 		send_eot();
// 	}
// 	else
// 	{
// 		write(1, "-client error-\nno valid g_msg\n", \
// 			ft_strlen("-client error-\nno valid g_msg\n"));
// 	}
// 	return (0);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 02:27:10 by hstein            #+#    #+#             */
/*   Updated: 2023/08/02 23:06:56 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

static bool	RDY_FLAG;

static void	handler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;

	if (sig == SIGUSR1)
	{
		RDY_FLAG = true;
		ft_printf("rdy_flag true\n");

	}
	else
	{
		ft_printf("(handler in client.c) something happened\n");
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	s_sigaction;
	int					g_pid_server;

	s_sigaction.sa_sigaction = handler;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sigaction, NULL); //pruefen ob die pid vom server ist
	if (argc == 3)
	{
		uint32_t		*g_msg;

		g_pid_server = atoi(argv[1]);
		// send_stx();
		g_msg = (void *)argv[2];
		write(1, "\n#send - g_msg:", ft_strlen("\n#send - g_msg:"));
		write(1, argv[2], ft_strlen(argv[2]));
		send_msg(g_pid_server, g_msg);
		send_eot();
	}
	else
	{
		write(1, "-client error-\nno valid g_msg\n", \
			ft_strlen("-client error-\nno valid g_msg\n"));
	}
	return (0);
}
