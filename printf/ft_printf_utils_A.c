/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_A.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 21:34:53 by hstein            #+#    #+#             */
/*   Updated: 2023/02/02 21:34:53 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strjoinfree(char *s1, char const *s2)
{
	char	*join;

	if (!s1)
		return (ft_strdup(s2));
	join = ft_strjoin(s1, s2);
	free(s1);
	return (join);
}

void	ft_putnbrstr(char **ptr_ret_line, int n)
{
	if (n == -2147483648)
	{
		*ptr_ret_line = ft_strjoinfree(*ptr_ret_line, "-2147483648");
		return ;
	}
	if (n < 0)
	{
		*ptr_ret_line = ft_strjoinfree(*ptr_ret_line, "-");
		ft_putnbrstr(ptr_ret_line, -n);
	}
	else if (n > 9)
	{
		ft_putnbrstr(ptr_ret_line, n / 10);
		ft_putnbrstr(ptr_ret_line, n % 10);
	}
	else
		ft_putcharstr(ptr_ret_line, n + '0');
}

void	ft_putunbrstr(char **ptr_ret_line, unsigned int n)
{
	if (n > 9)
	{
		ft_putnbrstr(ptr_ret_line, n / 10);
		ft_putnbrstr(ptr_ret_line, n % 10);
	}
	else
		ft_putcharstr(ptr_ret_line, n + '0');
}

char	*ft_strhandler(char *ptr_ret_line, char *va_arg_str)
{
	if (va_arg_str)
		ptr_ret_line = ft_strjoinfree(ptr_ret_line, va_arg_str);
	else
		ptr_ret_line = ft_strjoinfree(ptr_ret_line, "(null)");
	if (!ptr_ret_line)
		return (NULL);
	return (ptr_ret_line);
}

char	*printtype(char **ptr_ret_line, char type, va_list *args)
{
	if (type == 'i' || type == 'd')
		ft_putnbrstr(ptr_ret_line, va_arg(*args, int));
	else if (type == 'u')
		ft_putunbrstr(ptr_ret_line, va_arg(*args, int));
	else if (type == 'c')
		ft_putcharstr(ptr_ret_line, va_arg(*args, int));
	else if (type == 's')
	{
		*ptr_ret_line = ft_strhandler(*ptr_ret_line, va_arg(*args, char *));
		if (!ptr_ret_line)
			return (NULL);
	}
	else if (type == 'x')
		ft_putitoxstr(ptr_ret_line, va_arg(*args, unsigned int), 0);
	else if (type == 'X')
		ft_putitoxstr(ptr_ret_line, va_arg(*args, unsigned int), 1);
	else if (type == 'p')
		ft_getptradress(ptr_ret_line, va_arg(*args, void *));
	else if (type == '%')
		ft_putcharstr(ptr_ret_line, '%');
	else
		return (NULL);
	return (*ptr_ret_line);
}
