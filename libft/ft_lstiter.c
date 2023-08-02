/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 03:42:58 by hstein            #+#    #+#             */
/*   Updated: 2023/01/03 03:42:58 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	Function name		ft_lstiter
	Prototype			void ft_lstiter(t_list *lst, void (*f)(void *));
	Turn in files		-
	Parameters lst:		The address of a pointer to a node.
	f:					The address of the function used to iterate on the list.
	Return value		None
	External functs.	None
	Description			Iterates the list ’lst’ and applies the function
						’f’ on the content of each node.
*/

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst && f)
	{
		while (lst != NULL)
		{
			f(lst->content);
			lst = lst->next;
		}
	}
}
