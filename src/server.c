/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 02:27:19 by hstein            #+#    #+#             */
/*   Updated: 2023/08/02 23:12:34 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

static uint32_t	g_incoming_type;
static uint32_t	g_bits;
static uint32_t	g_bitsize;
static uint32_t	client_pid;
// static bool		busy;

// void	check_pids(int pid, int *clients, int cnt_clients)
// {
// 	int	i;

// 	i = 0;
// 	while (i < cnt_clients)
// 	{
// 		if (clients[i] == pid)
// 		{
// 			printf("new pid here\n");
// 			return ;
// 		}
// 	}
// 	printf("NO new pid here\n");
// }

static void	handler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;

	if (sig == SIGUSR1 || sig == SIGUSR2)
	{
		client_pid = info->si_pid;
		if (sig == SIGUSR1)
		{
			g_incoming_type |= (1 << g_bits);
			g_bits++;
		}
		else if (sig == SIGUSR2)
		{
			g_bits++;
		}
	}
	else
	{
		ft_printf("(handler in server.c) something happened\n");
		exit(0);
	}
}
// union sigval {
// 	int sival_int;
// 	void *sival_ptr;
// };
// typedef struct {
// 	int si_signo;
// 	int si_code;
// 	union sigval si_value;
// 	int si_errno;
// 	pid_t si_pid;
// 	uid_t si_uid;
// 	void *si_addr;
// 	int si_status;
// 	int si_band;
// } siginfo_t;
int	main(void)
{
	struct sigaction	s_sigaction;
	static size_t		bytes;

	s_sigaction.sa_sigaction = handler;
	s_sigaction.sa_flags = SA_SIGINFO;
	ft_printf("Server runs ..\nPID:%d\n\n", getpid());
	sigaction(SIGUSR1, &s_sigaction, NULL);
	sigaction(SIGUSR2, &s_sigaction, NULL);
	while (1)
	{
		if (g_bits >= g_bitsize)
		{
			if (g_incoming_type == 4)
			{
				ft_printf("\n");
				// kill(client_pid, SIGUSR1);
			}
			// busy = false;
			write(1, &g_incoming_type, 1);
			g_bits = 0;
			g_incoming_type = 0;
			bytes++;
		}
	}
	return (0);
}

// wenn bytes are reached dann send sigusr1 to client. client recieved und printed bestaetigung
// 