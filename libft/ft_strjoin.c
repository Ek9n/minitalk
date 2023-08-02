/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 00:08:11 by hstein            #+#    #+#             */
/*   Updated: 2022/12/19 00:08:11 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1_prefix;
	size_t	len_s2_suffix;
	char	*join;

	len_s1_prefix = ft_strlen(s1);
	len_s2_suffix = ft_strlen(s2);
	join = malloc(len_s1_prefix + len_s2_suffix + 1);
	if (!join)
		return (NULL);
	ft_strlcpy(join, s1, len_s1_prefix + 1);
	ft_strlcat(join, s2, len_s1_prefix + len_s2_suffix + 1);
	return (join);
}
