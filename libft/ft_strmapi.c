/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 21:43:04 by hstein            #+#    #+#             */
/*   Updated: 2022/12/20 21:43:04 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Function name:		ft_strmapi
	Prototype:			char *ft_strmapi(char const *s, char (*f)(unsigned int, char));
	Turn in files:		-
	Parameters:			s: The string on which to iterate.
						f: The function to apply to each character.				
	Return value:		The string created from the successive applications of ’f’.
						Returns NULL if the allocation fails.
	External functs.:	malloc
	Description:		Applies the function ’f’ to each character of the
						string ’s’, and passing its index as first argument
						to create a new string (with malloc(3)) resulting
						from successive applications of ’f’.
*/

#include "libft.h"

static	char	*ft_createstr(size_t strlen)
{
	char	*str;

	str = malloc(strlen + 1);
	if (str)
	{
		str[strlen] = '\0';
		return (str);
	}
	return (NULL);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*nstr;
	unsigned int	i;

	nstr = ft_createstr(ft_strlen(s));
	if (!nstr)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		nstr[i] = f(i, s[i]);
		i++;
	}
	return (nstr);
}
