/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 02:27:19 by hstein            #+#    #+#             */
/*   Updated: 2023/08/02 03:26:48 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

uint32_t	incoming_type;
// size_t	incoming_type;
static uint32_t	bits;

static void	handler(int sig)
{

		if (sig == SIGUSR1)
		{
			// ft_printf("SIGUSR1-signal recieved\n");
			// write(1, "1", 1);
			incoming_type |= (1 << bits);
			bits++;
		}
		else if (sig == SIGUSR2)
		{
			// ft_printf("SIGUSR2-signal recieved\n");
			// write(1, "0", 1);
			bits++;
		}
		else
		{
			ft_printf("(handler) something happened\n");
			exit(0);
		}
}


int main(void)
{
	const uint32_t	bitsize = 8;
	ft_printf("Server runs ..\nPID:%d\n\n", getpid());

	incoming_type = 0;
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	while (1)
    {
		if (bits >= bitsize)
		{

			// write(1, "\n", 1);
			// ft_printf("\nINCOMING CHAR:%c\n", (char)incoming_type);
			if (incoming_type == 4)
				ft_printf("\n");
			write(1, &incoming_type, 1);
			bits = 0;
			incoming_type = 0;
			// sleep(1);
		}
		
    }
	return (0);
}
