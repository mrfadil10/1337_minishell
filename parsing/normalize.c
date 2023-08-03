/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:18:10 by mfadil            #+#    #+#             */
/*   Updated: 2023/07/29 11:23:34 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_tabdup(char **av)
{
	int		i;
	char	**new;

	if (!av)
		return (NULL);
	new = back_alloc(sizeof(char *) * (ft_tablen(av) + 1), 1);
	i = -1;
	while (av[++i])
		new[i] = type_strdup(av[i], 1);
	new[i] = NULL;
	return (new);
}

void	ft_myadd_front(t_data **data, t_data **tmp, char **cmd)
{
	t_data	*node;
	t_data	*prev;

	node = back_alloc(sizeof(t_data), 1);
	node->t_type = COMMND;
	node->av = ft_tabdup(cmd);
	prev = (*tmp)->prev;
	(*tmp)->prev = node;
	node->prev = prev;
	node->next = *tmp;
	if (!prev)
		*data = node;
	else
		prev->next = node;
}

void	part_of_normalize(t_data **new_data)
{
	t_data	*tmp;
	char	**tab;

	tmp = *new_data;
	while (tmp)
	{
		if ((tmp->t_type == ADD || tmp->t_type == HRDC
				|| tmp->t_type == SUPERIOR || tmp->t_type == INFERIOR)
			&& ft_tablen(tmp->next->av) > 1)
		{
			if (tmp->prev == NULL || tmp->prev->t_type == PIPE)
				ft_myadd_front(new_data, &tmp, &tmp->next->av[1]);
			else
			{
				tab = tmp->prev->av;
				tmp->prev->av = ft_tabjoin(tmp->prev->av, &tmp->next->av[1]);
			}
		}
		if (tmp->av)
		{
			tmp->ac = ft_tablen(tmp->av);
			tmp->commands = type_strdup(tmp->av[0], 1);
		}
		tmp = tmp->next;
	}
}

t_data	*normalize(t_data *data)
{
	t_data	*new_data;
	t_data	*tmp;
	t_data	*data_prev;

	new_data = NULL;
	tmp = data;
	while (data != NULL)
	{
		data_prev = data->prev;
		if (data_prev == NULL)
		{
			add_back(&new_data, data);
		}
		else if ((data->t_type == SIQUOTE || data->t_type == DOQUOTE
				|| data->t_type == COMMND)
			&& (data_prev->t_type == SIQUOTE || data_prev->t_type == DOQUOTE
				|| data_prev->t_type == COMMND))
		{
			tab_concat(ft_mylstlast(new_data), data);
		}
		else
			add_back(&new_data, data);
		data = data->next;
	}
	new_data->prev = NULL;
	part_of_normalize(&new_data);
	return (new_data);
}
