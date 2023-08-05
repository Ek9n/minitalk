/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 02:27:19 by hstein            #+#    #+#             */
/*   Updated: 2023/08/04 05:46:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

uint32_t		g_incoming_type;
static uint32_t	g_bits;
static int		g_client_pid;
static bool		busy;

static void	handler(int sig, siginfo_t *info, void *context)
{
	// (void)info;
	(void)context;

	if (!busy) //was ist wenn vorher ein signal gesendet wird und es keine 6 ist... abfangen (eventuell flag fuer 1 byte recieved)
	// if (!g_client_pid || !busy) //was ist wenn vorher ein signal gesendet wird und es keine 6 ist... abfangen (eventuell flag fuer 1 byte recieved)
	{
		// printf("SHIT\n");
		g_client_pid = info->si_pid;
		busy = true;
	}
	// printf("busyflag=%d\n", busy);
	if (info->si_pid == g_client_pid && busy)
	{
		if (sig == SIGUSR1 && info->si_pid == g_client_pid)
		{
			// ft_printf("in handler SIGUSR1 1\n");
			g_incoming_type |= (1 << g_bits);
			g_bits++;
			// ft_printf("g_bits:%d\n", g_bits);
		}
		else if (sig == SIGUSR2 && info->si_pid == g_client_pid)
		{
			// ft_printf("in handler SIGUSR2 0\n");
			g_bits++;
		}
		else if (info->si_pid == g_client_pid)
		{
			ft_printf("(handler) something happened\n");
			exit(0);
		}
	}
}

int	main(void)
{
	struct sigaction	s_sigaction;
	uint32_t			byte;
	static bool			first_byte;

	s_sigaction.sa_sigaction = handler;
	s_sigaction.sa_flags = SA_SIGINFO;
	byte = 8;
	g_incoming_type = 0;

	ft_printf("Server runs ..\nPID:%d\n\n", getpid());
	sigaction(SIGUSR1, &s_sigaction, NULL);
	sigaction(SIGUSR2, &s_sigaction, NULL);
	while (1)
	{//here ist das problem
				// ft_printf("%d\n", g_bits); //bytes
		if (g_bits >= byte)
		{	
			if (g_incoming_type == 6 && !first_byte)
			{
				ft_printf("#MSG incoming\n");
				// ft_printf("client_ID:%d\n", g_client_pid);
					g_bits = 0;
					g_incoming_type = 0;
					busy = true;
					kill(g_client_pid, SIGUSR1); // send ok to client
				// usleep(10000);
				first_byte = true;
			}
			if (!first_byte)////////kann raus?                01 110
			{
				ft_printf("firrrrrst c:%d\n", g_incoming_type);
				g_bits = 0;
				g_incoming_type = 0;
				// first_byte = false;
				busy = false;
			}
			else if (g_incoming_type != 6 && !first_byte)
			{
				g_bits = 0;
				g_incoming_type = 0;
				first_byte = false;
				busy = false;
			}
			else if (g_incoming_type == 4)
			{
				ft_printf("\n");
				ft_printf("#MSG sent\n");
				for (int i = 0; i < 50; i++)
					kill(g_client_pid, SIGUSR2);
				// usleep(1000);
				g_bits = 0;
				g_incoming_type = 0;
				first_byte = false;
				busy = false;
			}
			if (busy)
				write(1, &g_incoming_type, 1);
			g_bits = 0;
			g_incoming_type = 0;
		}
 		pause();
	}
	return (0);
}
