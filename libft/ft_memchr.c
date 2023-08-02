/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 19:04:58 by hstein            #+#    #+#             */
/*   Updated: 2022/12/18 01:58:11 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*ptr_s;

	ptr_s = (char *)s;
	i = 0;
	while (i < n)
	{
		if (ptr_s[i] == (char)c)
			return (ptr_s + i);
		i++;
	}
	return (NULL);
}
