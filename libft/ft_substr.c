/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 00:43:24 by hstein            #+#    #+#             */
/*   Updated: 2022/12/13 21:29:46 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_s;
	size_t	new_len;
	char	*src;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	src = (char *)s + start;
	if (ft_strlen(src) < len)
		new_len = ft_strlen(src) + 1;
	else
		new_len = len + 1;
	new_s = (char *)malloc(new_len * sizeof(char));
	if (!new_s)
		return (NULL);
	ft_strlcpy(new_s, src, new_len);
	return (new_s);
}
