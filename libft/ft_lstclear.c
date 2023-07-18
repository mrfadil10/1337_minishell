/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 09:55:09 by stemsama          #+#    #+#             */
/*   Updated: 2022/10/16 09:55:09 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*p;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		p = (*lst)->next;
		free((*lst));
		(*lst) = p;
	}
	*lst = NULL;
}
