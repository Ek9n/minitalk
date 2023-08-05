/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 02:27:19 by hstein            #+#    #+#             */
/*   Updated: 2023/08/05 18:14:45 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

void	print_byte(uint32_t *bits, uint32_t *incoming_type, int *client_pid)
{
	if (*bits >= 8)
	{
		if (*incoming_type == 4)
		{
			write(1, "\n", 1);
			kill(*client_pid, SIGUSR2);
			ft_printf("#MSG send\nServer_PID:%d\n\n", getpid());
			*client_pid = 0;
		}
		else
			write(1, incoming_type, 1);
		*bits = 0;
		*incoming_type = 0;
	}
}

static void	handler(int sig, siginfo_t *info, void *context)
{
	static uint32_t		bits;
	static uint32_t		incoming_type;
	static int			client_pid;

	(void) context;
	if (client_pid == 0)
		client_pid = info->si_pid;
	if ((sig == SIGUSR1 || sig == SIGUSR2) && (info->si_pid == client_pid))
	{
		kill(client_pid, SIGUSR1);
		if (sig == SIGUSR1)
		{
			incoming_type |= (1 << bits);
			bits++;
		}
		else if (sig == SIGUSR2)
			bits++;
		print_byte(&bits, &incoming_type, &client_pid);
	}
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
