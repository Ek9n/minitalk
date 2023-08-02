/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 02:27:19 by hstein            #+#    #+#             */
/*   Updated: 2023/08/02 03:36:10 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

uint32_t		g_incoming_type;
static uint32_t	g_bits;

static void	handler(int sig)
{
	if (sig == SIGUSR1)
	{
		g_incoming_type |= (1 << g_bits);
		g_bits++;
	}
	else if (sig == SIGUSR2)
	{
		g_bits++;
	}
	else
	{
		ft_printf("(handler) something happened\n");
		exit(0);
	}
}

int	main(void)
{
	const uint32_t	g_bitsize;

	g_bitsize = 8;
	g_incoming_type = 0;
	ft_printf("Server runs ..\nPID:%d\n\n", getpid());
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	while (1)
	{
		if (g_bits >= g_bitsize)
		{
			if (g_incoming_type == 4)
				ft_printf("\n");
			write(1, &g_incoming_type, 1);
			g_bits = 0;
			g_incoming_type = 0;
		}
	}
	return (0);
}
