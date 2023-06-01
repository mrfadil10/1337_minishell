/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 09:55:18 by stemsama          #+#    #+#             */
/*   Updated: 2022/10/16 09:55:18 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		a;

	a = 0;
	if (!lst)
		return (0);
	while (lst != 0)
	{
		lst = lst->next;
		a++;
	}
	return (a);
}
