/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 17:18:04 by hstein            #+#    #+#             */
/*   Updated: 2022/12/30 17:18:04 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	Function name		ft_lstclear
	Prototype			void ft_lstclear(t_list **lst, void (*del)(void	*));
	Turn in files		-
	Parameters lst:		The address of a pointer to a node.
	del:				The address of the function used to delete
						the content of the node.
	Return value		None
	External functs.	free()
	Description			Deletes and frees the given node and every
						successor of that node, using the function ’del’ and free(3).
						Finally, the pointer to the list must be set to NULL.
						
						typedef struct s_list
						{
						void			*content;
						struct s_list	*next;
						}	t_list;
*/

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (lst && *lst && del)
	{
		while (lst && *lst)
		{
			temp = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = temp;
		}
	}
}
