/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 21:12:59 by mfadil            #+#    #+#             */
/*   Updated: 2023/07/16 14:49:50 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



t_data	check_syntax(t_data *data)
{
	t_data	*node;
	t_data	*prev;
	t_data	*tmp;

	tmp = data;
	node = NULL;

	while (data)
	{
		prev = prev->next;
		if (!prev)


	}
}