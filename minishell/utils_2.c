/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 20:36:27 by mfadil            #+#    #+#             */
/*   Updated: 2023/07/12 19:27:30 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(int fd)
{
	t_collect	*data;
	t_collect	*tmp;

	if (!fd)
		data = g_data.end;
	else
		data = g_data.tmp;
	while (data)
	{
		tmp = data;
		data = data->next;
		if (tmp->data)
			free(tmp->data);
		tmp->data = NULL;
		free(tmp);
		data = data->next;
	}
	data = NULL;
	if (!fd)
		g_data.tmp = data;
	else
		g_data.end = data;
}
