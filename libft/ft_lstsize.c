/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 00:38:49 by hstein            #+#    #+#             */
/*   Updated: 2022/12/30 00:38:49 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*tmp;
	int		cnt;

	tmp = lst;
	cnt = 0;
	while (tmp)
	{
		cnt++;
		tmp = tmp->next;
	}
	return (cnt);
}
