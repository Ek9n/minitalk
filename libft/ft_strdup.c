/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 23:22:52 by hstein            #+#    #+#             */
/*   Updated: 2022/12/18 23:22:52 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	strsize;

	strsize = ft_strlen(s) + 1;
	dup = malloc(strsize);
	if (dup)
	{
		ft_strlcpy(dup, s, strsize);
		return (dup);
	}
	return (NULL);
}
