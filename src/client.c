/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 02:27:10 by hstein            #+#    #+#             */
/*   Updated: 2023/08/02 03:25:48 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

int					pid_server;
uint32_t			*msg;
const uint32_t		bitsize = 8;

void	send_char(int pid, uint32_t bitsize, char c)
{
		uint32_t	bit;
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

static void	send_msg(int pid, const uint32_t *msg)
{
	char		c;
	int			bitsize_msg = ft_strlen((char *)msg) * bitsize;
	int			bytesize_msg = ft_strlen((char *)msg);

	char		*cast_msg = (char *)msg;

	printf("\nBits sent: %d\n", bitsize_msg);

	c = *cast_msg;
	while (*cast_msg++ && bytesize_msg)
	{
		send_char(pid, bitsize, c);
		c = *cast_msg;
		bytesize_msg--;
	}

}

int main(int argc, char **argv)
{
	if (argc == 3)
	{
		pid_server = atoi(argv[1]);
		msg = (void *)argv[2];
		write(1, "#send - msg:", ft_strlen("#send - msg:"));
		write(1, argv[2], ft_strlen(argv[2]));
		send_msg(pid_server, msg);
		*msg = 4;
		write(1, "\n#send - end of transmission (EOT)", \
			ft_strlen("\n#send - end of transmission (EOT)"));
		send_msg(pid_server, msg);
	}
	else
	{
		write(1, "-client error-\nno valid msg\n", \
			ft_strlen("-client error-\nno valid msg\n"));
	}
	return (0);
}
