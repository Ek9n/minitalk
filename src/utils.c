/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 21:19:20 by hstein            #+#    #+#             */
/*   Updated: 2023/08/02 23:04:37 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"


static int		g_pid_server;
const uint32_t	g_bitsize = 8;

void	send_char(int pid, uint32_t bitsize, char c)
{
	uint32_t	bit;

    bitsize = g_bitsize;
	bit = -1;
	while (++bit < bitsize)
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

void	send_msg(int pid, const uint32_t *msg)
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

void	send_stx()
{
	uint32_t	msg;

	msg = 2;
	write(1, "\n#send - start of text (STX)", \
		ft_strlen("\n#send - start of text (STX)"));
	send_msg(g_pid_server, &msg);
}

void	send_eot()
{
	uint32_t	msg;

	msg = 4;
	write(1, "\n#send - end of transmission (EOT)", \
		ft_strlen("\n#send - end of transmission (EOT)"));
	send_msg(g_pid_server, &msg);
}