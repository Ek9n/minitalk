/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_B.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 21:35:01 by hstein            #+#    #+#             */
/*   Updated: 2023/02/02 21:35:01 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_putcharstr(char **ptr_ret_line, int c)
{
	char	add[2];

	if (c == '\0')
		c = 7;
	add[0] = (unsigned char)c;
	add[1] = '\0';
	*ptr_ret_line = ft_strjoinfree(*ptr_ret_line, add);
	if (!*ptr_ret_line)
		return (NULL);
	return (*ptr_ret_line);
}

void	ft_putitoxstr(char **ptr_ret_line, \
			size_t decimalnumber, char option)
{
	char	hexbase[16];
	char	hexreverse[8];
	int		cnt;

	if (decimalnumber != 0)
	{
		if (option == 0)
			ft_strlcpy(hexbase, "0123456789abcdef", 17);
		else if (option == 1)
			ft_strlcpy(hexbase, "0123456789ABCDEF", 17);
		cnt = 0;
		while (decimalnumber > 0)
		{
			hexreverse[cnt] = hexbase[decimalnumber % 16];
			decimalnumber /= 16;
			cnt++;
		}
		while (--cnt >= 0)
			ft_putcharstr(ptr_ret_line, hexreverse[cnt]);
	}
	else
		ft_putcharstr(ptr_ret_line, '0');
}

void	ft_getptradress(char **ptr_ret_line, void *ptr_adress)
{
	if (ptr_adress)
	{
		*ptr_ret_line = ft_strjoinfree(*ptr_ret_line, "0x");
		ft_putitoxstr(ptr_ret_line, (size_t) ptr_adress, 0);
	}
	else
		*ptr_ret_line = ft_strjoinfree(*ptr_ret_line, "(nil)");
}
