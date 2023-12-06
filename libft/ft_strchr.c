/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 19:04:14 by hstein            #+#    #+#             */
/*   Updated: 2023/01/06 21:55:55 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*ptr_s;

	ptr_s = (char *)s;
	i = 0;
	if (s[i] == (char)c && s[i] == '\0')
		return (ptr_s);
	while (s[i])
	{
		if (s[i] == (char)c)
			return (ptr_s + i);
		i++;
	}
	if (s[i] == (char)c)
		return (ptr_s + i);
	return (NULL);
}
