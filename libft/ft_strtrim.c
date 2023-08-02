/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 14:32:11 by hstein            #+#    #+#             */
/*   Updated: 2022/12/19 14:32:11 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_setchecker(char const c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s1_new;
	char	*s1_start;
	char	*s1_end;
	size_t	s1_len;

	if (!s1 || !set)
		return (NULL);
	s1_len = ft_strlen(s1);
	s1_start = (char *)s1;
	s1_end = s1_start + s1_len - 1;
	while (*s1_start && ft_setchecker(*s1_start, set))
		s1_start++;
	while (s1_end > s1_start && ft_setchecker(*s1_end, set))
		s1_end--;
	s1_new = malloc(s1_end - s1_start + 2);
	if (!s1_new)
		return (NULL);
	ft_strlcpy(s1_new, s1_start, s1_end - s1_start + 2);
	return (s1_new);
}
