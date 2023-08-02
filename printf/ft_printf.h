/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 21:35:15 by hstein            #+#    #+#             */
/*   Updated: 2023/02/02 21:35:15 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "../libft/libft.h"

// Declarations

int		ft_printf(const char *formatstr, ...);

// ft_printf_utils_A
char	*ft_strjoinfree(char *s1, char const *s2);
void	ft_putnbrstr(char **ptr_ret_line, int n);
void	ft_putunbrstr(char **ptr_ret_line, unsigned int n);
char	*printtype(char **ptr_ret_line, char type, va_list *args);
char	*ft_strhandler(char *ptr_ret_line, char *va_arg_str);

// ft_printf_utils_B
char	*ft_putcharstr(char **ptr_ret_line, int c);
void	ft_putitoxstr(char **ptr_ret_line, \
			size_t decimalnumber, char option);
void	ft_getptradress(char **ptr_ret_line, void *ptr_adress);

#endif
