/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:10:44 by mfadil            #+#    #+#             */
/*   Updated: 2023/08/06 18:36:44 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_tabjoin(char **s1, char **s2)
{
	char	**new_tab;
	int		i;
	int		j;
	int		lnt;

	if (!(*s1))
		return (s2);
	if (!(*s2))
		return (s1);
	lnt = ft_tablen(s1) + ft_tablen(s2) + 1;
	new_tab = (char **)back_alloc(lnt * sizeof(char *), 1);
	i = -1;
	j = -1;
	while (s1[++i])
		new_tab[i] = type_strdup(s1[i], 1);
	while (s2[++j])
		new_tab[i + j] = type_strdup(s2[j], 1);
	new_tab[i + j] = NULL;
	return (new_tab);
}

void	tab_concat(t_data *node, t_data *data)
{
	char	**tab;
	char	*tmp;
	int		i;

	i = ft_tablen(node->av) - 1;
	if (data->sp == 0)
	{
		tmp = node->av[i];
		node->av[i] = ft_mystrjoin(node->av[i], data->av[0]);
	}
	else
	{
		tab = node->av;
		node->av = ft_tabjoin(node->av, data->av);
	}
}

char	**dup_to_tab(char **str)
{
	char	**tab;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	tab = back_alloc(sizeof(char *) * (ft_tablen(str) + 1), 1);
	while (str[i])
	{
		tab[i] = type_strdup(str[i], 1);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

t_data	*ft_dup(t_data *data)
{
	t_data	*dup;

	dup = back_alloc(sizeof(t_data), 1);
	dup->t_type = data->t_type;
	dup->pipe[0] = data->pipe[0];
	dup->pipe[1] = data->pipe[0];
	dup->av = dup_to_tab(data->av);
	dup->next = NULL;
	return (dup);
}

void	add_back(t_data **node, t_data *data)
{
	t_data	*dup;
	t_data	*last;

	dup = ft_dup(data);
	if (!(*node))
		*node = dup;
	else
	{
		last = ft_mylstlast(*node);
		dup->prev = last;
		last->next = dup;
	}
}
