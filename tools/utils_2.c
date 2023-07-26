/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 20:36:27 by mfadil            #+#    #+#             */
/*   Updated: 2023/07/26 17:08:19 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_mystrjoin(char *s1, char *s2)
{
	char	*new_str;
	int		i;
	int		j;
	int		lnt;

	lnt = ft_strlen(s1) + ft_strlen(s2) + 1;
	new_str = (char *)back_alloc(lnt * sizeof(char), 1);
	i = -1;
	while (s1[++i])
		new_str[i] = s1[i];
	j = -1;
	while (s2[++j])
		new_str[i + j] = s2[j];
	new_str[i + j] = 0;
	return (new_str);
}

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
