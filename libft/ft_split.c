/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 15:25:02 by hstein            #+#    #+#             */
/*   Updated: 2022/12/19 15:25:02 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_cntstr(char const *s, char c)
{
	size_t	cnt;
	size_t	i;

	cnt = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			cnt++;
			while (s[i + 1] != '\0' && s[i] != c)
				i++;
		}
		i++;
	}
	return (cnt);
}

static char	**ft_makearray(char const *s, char c)
{
	char	**arr;
	size_t	cntstr;

	cntstr = ft_cntstr(s, c);
	arr = malloc((cntstr + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	arr[cntstr] = NULL;
	return (arr);
}

static char	**ft_writeword(char **array, const char **ptr_hold, \
								const char **ptr_move, char **words)
{
	*words = malloc(*ptr_move - *ptr_hold + 1);
	if (!*words)
	{
		words = array;
		while (*words != NULL)
		{
			free(*words);
			words = words + 1;
		}
		free(array);
		return (NULL);
	}
	ft_strlcpy(*words, *ptr_hold, *ptr_move - *ptr_hold + 1);
	*ptr_hold = *ptr_move;
	return (++words);
}

static void	ft_skipc(const char **ptr_hold, char c)
{
	while (**ptr_hold && **ptr_hold == c)
		(*ptr_hold)++;
}

char	**ft_split(char const *s, char c)
{
	char		**array;
	char		**words;
	const char	*ptr_hold;
	const char	*ptr_move;

	array = ft_makearray(s, c);
	if (!array)
		return (NULL);
	words = array;
	ptr_hold = (const char *)s;
	ft_skipc(&ptr_hold, c);
	while (*ptr_hold != '\0')
	{
		if (*ptr_hold != c)
		{
			ptr_move = ptr_hold;
			while (*ptr_move != c && *ptr_move)
				ptr_move++;
			words = ft_writeword(array, &ptr_hold, &ptr_move, words);
			if (!words)
				return (NULL);
			ft_skipc(&ptr_hold, c);
		}
	}
	return (array);
}
