/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 11:23:19 by mfadil            #+#    #+#             */
/*   Updated: 2023/07/16 18:39:03 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_collect	*type_lstlast(t_collect *lst)
{
	t_collect	*tmp;

	if (lst == NULL)
		return (NULL);
	tmp = lst;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	return (tmp);
}

t_collect	*type_lstnew(void *content)
{
	t_collect	*b;

	b = (t_collect *)malloc(sizeof(t_collect));
	if (!b)
		exit (1);
	b->data = content;
	b->next = NULL;
	return (b);
}

void	type_lstadd_back(void *ptr, int type)
{
	t_collect	*data;

	if (!type)
		data = g_data.end;
	else
		data = g_data.tmp;
	if (!data)
	{
		data = type_lstnew(ptr);
		if (!type)
			g_data.end = data;
		else
			g_data.tmp = data;
	}
	else
		type_lstlast(data)->next = type_lstnew(ptr);
}

void	*back_alloc(unsigned long lnt, int type)
{
	void	*ptr;

	ptr = malloc(lnt);
	if (!ptr)
		exit (1);
	type_lstadd_back(ptr, type);
	return (ptr);
}

char	*type_substr(const char *str, unsigned int start, int type, size_t lnt)
{
	char			*new_str;
	unsigned long	c;

	if (!str)
		return (NULL);
	if (ft_strlen(str) < start)
	{
		new_str = back_alloc(1, type);
		if (!new_str)
			return (NULL);
		new_str[0] = '\0';
		return (new_str);
	}
	if (ft_strlen(str) < lnt)
		lnt = ft_strlen(str);
	new_str = (char *)back_alloc(sizeof(char) * lnt + 1, type);
	c = 0;
	while (start < ft_strlen(str) && c < lnt)
	{
		new_str[c] = str[start];
		start++;
		c++;
	}
	new_str[c] = '\0';
	return (new_str);
}
