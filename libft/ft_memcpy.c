/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 19:02:10 by hstein            #+#    #+#             */
/*   Updated: 2023/01/06 23:43:55 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*ptr_dest;
	const char	*ptr_src;
	void		*ret;

	if (!dest && !src)
		return (NULL);
	ret = dest;
	ptr_dest = (char *) dest;
	ptr_src = (char *) src;
	while (n--)
		*ptr_dest++ = *ptr_src++;
	return (ret);
}
