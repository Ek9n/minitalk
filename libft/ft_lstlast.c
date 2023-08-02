/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 01:45:41 by hstein            #+#    #+#             */
/*   Updated: 2022/12/30 01:45:41 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
		return (lst);
	}
	return (NULL);
}
/*
int main ()
{
	t_list *begin;
	t_list *e1;
	t_list *e2;
	t_list *e3;

	begin = NULL;

	e3 = ft_lstnew("Erstes ");
	e2 = ft_lstnew("Zweites ");
	e1 = ft_lstnew("Drittes");

	ft_lstadd_front(&begin, e3);
	ft_lstadd_front(&begin, e2);
	ft_lstadd_front(&begin, e1);

	printf("Nodes:%i, Inhalt des Letzten Elements:%s\n", \
	5, (char *)ft_lstlast(begin)->content);

}*/