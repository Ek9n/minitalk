/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 02:27:19 by hstein            #+#    #+#             */
/*   Updated: 2023/08/02 04:12:15 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

uint32_t		g_incoming_type;
static uint32_t	g_bits;

static void	handler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
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
	struct sigaction	s_sigaction;
	uint32_t			g_bitsize;

	s_sigaction.sa_sigaction = handler;
	s_sigaction.sa_flags = SA_SIGINFO;
	g_bitsize = 8;
	g_incoming_type = 0;
	ft_printf("Server runs ..\nPID:%d\n\n", getpid());
	sigaction(SIGUSR1, &s_sigaction, NULL);
	sigaction(SIGUSR2, &s_sigaction, NULL);
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
