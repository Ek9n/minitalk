/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 02:27:10 by hstein            #+#    #+#             */
/*   Updated: 2023/08/05 23:08:39 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

void	send_char(int pid, uint32_t bitsize, char c)
{
	uint32_t	bit;

	bit = -1;
	while (++bit < bitsize)
	{
		if (c >> bit & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(140);
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
	printf("\nBits sent: %d\n", bitsize_msg);
	c = *cast_msg;
	while (*cast_msg++ && bytesize_msg)
	{
		send_char(pid, bitsize, c);
		c = *cast_msg;
		bytesize_msg--;
	}
}

int	main(int argc, char **argv)
{
	int					pid_server;
	uint32_t			*msg;
	uint32_t			bitsize;
	uint32_t			eot;

	eot = 10;
	bitsize = 8;
	if (argc == 3)
	{
		pid_server = atoi(argv[1]);
		msg = (void *)argv[2];
		write(1, "#send - msg:", ft_strlen("#send - msg\n..."));
		send_msg(pid_server, msg, bitsize);
		send_msg(pid_server, &eot, bitsize);
		ft_printf("\n#send - end of transmission (EOT)");
	}
	else
		ft_printf("-client error-\nno valid msg\n");
	return (0);
}
