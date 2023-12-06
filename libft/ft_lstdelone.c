/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 15:35:38 by hstein            #+#    #+#             */
/*   Updated: 2022/12/30 15:35:38 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	Function name		ft_lstdelone
	Prototype			void ft_lstdelone(t_list *lst, void (*del)(void *));
	Turn in files		-
	Parameters lst:		The node to free.
	del:				The address of the function used to delete the content.
	Return value		None
	External functs.	free()
	Description			Takes as a parameter a node and frees the memory of the node’s
						content using the function ’del’ given as a parameter and free the node. 
						The memory of ’next’ must not be freed.

						typedef struct s_list
						{
						void			*content;
						struct s_list	*next;
						}	t_list;
*/

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst && del)
	{
		del(lst->content);
		free(lst);
	}
}
