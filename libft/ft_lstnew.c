/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 19:37:00 by hstein            #+#    #+#             */
/*   Updated: 2022/12/28 19:37:00 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Description
Function name		ft_lstnew
Prototype			t_list *ft_lstnew(void *content);
Turn in files		-
Parameters content: The content to create the node with.
Return value		The new node
External functs.	malloc
Description			Allocates (with malloc(3)) and returns a new node.
					The member variable ’content’ is initialized with
					the value of the parameter ’content’. The variable
					’next’ is initialized to NULL.
----------------------------------------------------------------------
	typedef struct s_list
	{
		void			*content;
		struct s_list	*next;
	}	t_list;
*/

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

// int	main()
// {
// 	t_list *list;
// 	char	str[] = "One";

// 	list = ft_lstnew(str);
// }