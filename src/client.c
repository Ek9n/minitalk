/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 02:27:10 by hstein            #+#    #+#             */
/*   Updated: 2023/08/02 03:33:34 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

int				g_pid_server;
uint32_t		*g_msg;
const uint32_t	g_bitsize = 8;

void	send_char(int pid, uint32_t g_bitsize, char c)
{
	uint32_t	bit;

	bit = -1;
	while (++bit < g_bitsize)
	{
		if (c >> bit & 1)
		{
			write(1, "1", 1);
			kill(pid, SIGUSR1);
		}
		else
		{
			write(1, "0", 1);
			kill(pid, SIGUSR2);
		}
		usleep(100);
	}
}

static void	send_g_msg(int pid, const uint32_t *g_msg)
{
	char		c;
	int			g_bitsize_g_msg;
	int			bytesize_g_msg;
	char		*cast_g_msg;

	g_bitsize_g_msg = ft_strlen((char *)g_msg) * g_bitsize;
	bytesize_g_msg = ft_strlen((char *)g_msg);
	cast_g_msg = (char *)g_msg;
	printf("\nBits sent: %d\n", g_bitsize_g_msg);
	c = *cast_g_msg;
	while (*cast_g_msg++ && bytesize_g_msg)
	{
		send_char(pid, g_bitsize, c);
		c = *cast_g_msg;
		bytesize_g_msg--;
	}
}

int	main(int argc, char **argv)
{
	if (argc == 3)
	{
		g_pid_server = atoi(argv[1]);
		g_msg = (void *)argv[2];
		write(1, "#send - g_msg:", ft_strlen("#send - g_msg:"));
		write(1, argv[2], ft_strlen(argv[2]));
		send_g_msg(g_pid_server, g_msg);
		*g_msg = 4;
		write(1, "\n#send - end of transmission (EOT)", \
			ft_strlen("\n#send - end of transmission (EOT)"));
		send_g_msg(g_pid_server, g_msg);
	}
	else
	{
		write(1, "-client error-\nno valid g_msg\n", \
			ft_strlen("-client error-\nno valid g_msg\n"));
	}
	return (0);
}
