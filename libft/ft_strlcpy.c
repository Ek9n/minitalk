/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 19:02:33 by hstein            #+#    #+#             */
/*   Updated: 2023/01/19 16:48:13 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	char		*ptr_dst;
	const char	*ptr_src;
	size_t		i;

	ptr_dst = dst;
	ptr_src = src;
	i = 0;
	if (dstsize > 0)
	{
		while (i < dstsize - 1 && *(ptr_src + i) != '\0')
		{
			*(ptr_dst + i) = *(ptr_src + i);
			i++;
		}
		*(ptr_dst + i) = '\0';
	}
	return (ft_strlen(src));
}
