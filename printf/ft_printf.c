/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 21:35:09 by hstein            #+#    #+#             */
/*   Updated: 2023/02/02 21:35:09 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_strlen_nullsub(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == 7)
			s[i] = '\0';
		i++;
	}
	return (i);
}

static void	ft_putnstr_fd(char *s, int n, int fd)
{	
	int	i;

	i = 0;
	while (i < n)
	{
		write(fd, &s[i], 1);
		i++;
	}
}

static char	*ft_writeline(char **ptr_ret_line, \
								const char *formatstr, va_list *args)
{
	int	i;

	i = 0;
	while (formatstr[i])
	{
		if (formatstr[i] == '%')
		{
			i++;
			if (printtype(ptr_ret_line, formatstr[i], args))
				i++;
		}
		else
		{
			ft_putcharstr(ptr_ret_line, formatstr[i]);
			i++;
		}
	}
	return (*ptr_ret_line);
}

int	ft_printf(const char *formatstr, ...)
{
	va_list	args;
	char	*ret_line;
	int		ret_len;

	if (!formatstr)
		return (-1);
	ret_len = 0;
	ret_line = ft_strdup("\0");
	if (!ret_line)
		return (0);
	va_start(args, formatstr);
	ret_line = ft_writeline(&ret_line, (const char *)formatstr, &args);
	if (!ret_line)
		return (0);
	va_end(args);
	ret_len = ft_strlen_nullsub(ret_line);
	ft_putnstr_fd(ret_line, ret_len, 1);
	free(ret_line);
	return (ret_len);
}

/*
// cc -Wall -Wextra -Werror main.c libftprintf.a libft/libft.a && ./a.out
int	main(void)
{	
	int c = 5;
	printf("bla%c nls", 0);
	ft_printf("ft_printf:\n%x, %X, %p, %p\n", 666, 666, NULL, &c);
	printf("printf:\n%x, %X, %p, %p\n", 666, 666, NULL, &c);
	ft_printf("");

	c = printf(0);
	printf("\n%d", c);
	c = ft_printf(0);
	printf("\n%d", c);
	// printf("\n\n");

	// int c;
	// ft_printf("\nft_printf:\n");
	// c = ft_printf("| %c %c %c |", '2', '1', 0);
	// printf("\nReturn:%i\n", c);
	// // ft_printf(" %p %p ", 0, 0);

	// // ft_printf("\nprintf:\n");
	// // c = printf("| %c %c %c |", '2', '1', 0);
	// // printf("\nReturn:%i\n", c);
	// ft_printf(" %p %p ", 0, 0);

	// c = ft_printf("| %c %c %c |", '2', '1', 0);
	// printf("\nReturn:%i\n", c);

	// ft_printf("\nprintf:\n");
	// c = printf("| %c %c %c |", '2', '1', 0);

	// c = printf("Hi%  d", 2);

	// printf("\nReturn_printf:%i\n", c);
	// ft_printf("ss%hhh%");

	// printf("Hal%clo\n", '\0');

	// ft_putchar_fd('H', 1);
	// ft_putchar_fd('\0', 1);
	// ft_putchar_fd('H', 1);


	// ft_printf(" %c %c %c ", '0', 0, '1');


	return (0);
}
*/