/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 19:05:36 by hstein            #+#    #+#             */
/*   Updated: 2023/01/06 22:36:07 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char	*big, const char *little, size_t len)
{
	const char		*ptr_big;
	const char		*ptr_little;
	size_t			len_little;
	size_t			i;

	ptr_big = big;
	ptr_little = little;
	if (!(*little))
		return ((char *) ptr_big);
	len_little = ft_strlen(little);
	i = 0;
	while (ptr_big[i] && i < len
		&& len_little <= len && (i + len_little <= len))
	{
		if (ptr_big[i] == ptr_little[0] || len_little == 0)
			if (ft_memcmp(&ptr_big[i], ptr_little, len_little) == 0)
				return ((char *) &ptr_big[i]);
		i++;
	}
	return (NULL);
}
