/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 20:36:27 by mfadil            #+#    #+#             */
/*   Updated: 2023/08/05 16:22:41 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**tab_fixed(char **str)
{
	int		i;
	int		j;
	char	**newtab;
	int		lnt;

	i = 0;
	lnt = ft_tablen(str);
	while (str[i])
	{
		if (str[i++][0] == '\0')
			lnt--;
	}
	i = 0;
	j = 0;
	newtab = back_alloc(sizeof(char *) * (lnt + 1), 1);
	while (str[i])
	{
		if (str[i][0])
			newtab[j++] = type_strdup(str[i], 1);
		i++;
	}
	newtab[j] = NULL;
	return (newtab);
}

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

char	*delete_one(char *str, int idx, int c)
{
	char	*new;
	int		i;
	int		j;

	new = back_alloc(sizeof(char) * ft_strlen(str) - 1, 1);
	if (!new)
		exit(1);
	i = 0;
	j = 0;
	while (str[i])
	{
		while (i == c || i == idx)
			i++;
		if (str[i] == '\0')
			break ;
		new[j++] = str[i++];
	}
	new[j] = '\0';
	return (new);
}

void	handle_quotes(t_data *data)
{
	int		i;
	int		j;

	i = -1;
	while (data->av[++i])
	{
		j = 0;
		while (data->av[i][j])
		{
			if (data->av[i][j] == '\'' || data->av[i][j] == '"')
			{
				if (part_of_delete_quote(data, i, &j))
					break ;
			}
			else
				j++;
		}
	}
}
