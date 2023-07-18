/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listnew_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 09:54:51 by stemsama          #+#    #+#             */
/*   Updated: 2022/10/16 09:54:51 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(int content)
{
	t_list	*b;

	b = (t_list *)malloc(sizeof(t_list));
	if (!b)
	{
		return (NULL);
	}
	b->content = content;
	b -> next = NULL;
	return (b);
}

t_list	*ft_lstnew_ind(int content, int index)
{
	t_list	*b;

	b = (t_list *)malloc(sizeof(t_list));
	if (!b)
	{
		return (NULL);
	}
	b->content = content;
	b->index = index;
	b -> next = NULL;
	return (b);
}
