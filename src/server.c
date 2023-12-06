/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 02:27:19 by hstein            #+#    #+#             */
/*   Updated: 2023/08/05 22:33:59 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

void	print_byte(uint32_t *bits, uint32_t *incoming_type)
{
	if (*bits >= 8)
	{
		write(1, incoming_type, 1);
		*bits = 0;
		*incoming_type = 0;
	}
}

static void	handler(int sig, siginfo_t *info, void *context)
{
	static uint32_t		bits;
	static int			client_pid;
	static uint32_t		incoming_type;

	(void) context;
	if (client_pid == 0)
		client_pid = info->si_pid;
	if (sig == SIGUSR1)
	{
		incoming_type |= (1 << bits);
		bits++;
	}
	else if (sig == SIGUSR2)
		bits++;
	else
	{
		ft_printf("(handler) something happened\n");
		exit(0);
	}
	print_byte(&bits, &incoming_type);
}

int	main(void)
{
	struct sigaction	s_sigaction;

	s_sigaction.sa_sigaction = handler;
	s_sigaction.sa_flags = SA_SIGINFO;
	ft_printf("Server runs ..\nPID:%d\n\n", getpid());
	sigaction(SIGUSR1, &s_sigaction, NULL);
	sigaction(SIGUSR2, &s_sigaction, NULL);
	while (1)
	{
	}
	return (0);
}
