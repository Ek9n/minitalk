/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 02:27:19 by hstein            #+#    #+#             */
/*   Updated: 2023/08/05 02:05:12 by hstein           ###   ########.fr       */
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

void	handler(int sig)
{
	static uint32_t		bits;
	static uint32_t		incoming_type;

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

	s_sigaction.sa_flags = 0;
	s_sigaction.sa_handler = handler;
	ft_printf("Server runs ..\nPID:%d\n\n", getpid());
	sigaction(SIGUSR1, &s_sigaction, NULL);
	sigaction(SIGUSR2, &s_sigaction, NULL);
	while (1)
	{
	}
	return (0);
}
