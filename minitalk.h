/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 01:50:00 by hstein            #+#    #+#             */
/*   Updated: 2023/08/02 23:08:00 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdbool.h>
#include "./libft/libft.h"
#include "./printf/ft_printf.h"

// int				g_pid_server;
// const uint32_t	g_bitsize = 8;

void	send_char(int pid, uint32_t bitsize, char c);
void	send_msg(int pid, const uint32_t *msg);
void	send_stx();
void	send_eot();