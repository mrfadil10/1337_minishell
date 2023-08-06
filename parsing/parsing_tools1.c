/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 19:59:54 by mfadil            #+#    #+#             */
/*   Updated: 2023/08/06 22:09:32 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*type_strdup(const char *src, int type)
{
	char	*dup;
	int		len;
	int		i;

	len = ft_strlen(src);
	dup = (char *)back_alloc(sizeof(char) * (len + 1), type);
	i = 0;
	while (i < len)
	{
		dup[i] = src[i];
		i++;
		dup[i] = 0;
	}
	dup[len] = 0;
	return (dup);
}

t_data	*new_data(t_data *prev, char *str, int t_type)
{
	t_data	*new_data;

	new_data = back_alloc(sizeof(t_data), 1);
	new_data->t_type = t_type;
	if (t_type == SIQUOTE || t_type == DOQUOTE)
	{
		new_data->av = back_alloc(sizeof(char *) * 2, 1);
		new_data->av[0] = type_strdup(str, 1);
		new_data->av[1] = 0;
	}
	else
		new_data->av = ft_split(str, ' ');
	new_data->prev = prev;
	new_data->next = NULL;
	return (new_data);
}

t_data	*ft_mylstlast(t_data *list)
{
	t_data	*tmp;

	if (list == NULL)
		return (NULL);
	tmp = list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

void	put_back(t_data **data, char *str, int t_type, int lnt)
{
	t_data	*list;
	char	*s;

	if (str && (t_type == SIQUOTE || t_type == DOQUOTE || t_type == COMMND))
		s = type_substr(str - lnt, 0, 1, lnt);
	else
		s = NULL;
	if (!(*data))
		*data = new_data(NULL, s, t_type);
	else
	{
		list = ft_mylstlast(*data);
		list->next = new_data(list, s, t_type);
	}
}

int	part_of_delete_quote(t_data *data, int i, int *j)
{
	char	*tmp;
	int		quote;
	int		y;

	quote = 0;
	if (data->av[i][*j] == '"')
		quote = '"';
	if (data->av[i][*j] == '\'')
		quote = '\'';
	if (quote != 0)
	{
		y = (*j)++;
		while (data->av[i][*j] && data->av[i][*j] != quote)
			(*j)++;
		if (data->av[i][*j] == 0)
			return (1);
		tmp = data->av[i];
		data->av[i] = delete_one(tmp, y,*j);
		*j -= 1;
		if (!data->av[i][*j])
			return (1);
	}
	return (0);
}
