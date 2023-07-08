/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 23:35:48 by stemsama          #+#    #+#             */
/*   Updated: 2023/06/06 23:00:50 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back2(t_data **lst, t_data *new)
{
	t_data	*tmp;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		new->next = NULL;
		return ;
	}
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}

t_data	*ft_lstnew_ind2(char *content)
{
	t_data	*b;

	b = (t_data *)malloc(sizeof(t_data));
	if (!b)
		return (NULL);
	b->name = get_name(content);
	b->value = get_value1(content);
	b->n_v = content;
	b->next = NULL;
	return (b);
}

char	*get_name(char *str)
{
	char	*name;

	name = ft_strchr(str, '=');
	if (!name)
		return (str);
	return (ft_substr(str, 0, ft_strlen(str) - ft_strlen(name)));
}

char	*get_value1(char *str)
{
	return (ft_strchr(str, '='));
}

t_data	*sort_env(t_data **env)
{
	t_data	*cur;
	char	*sp;

	cur = *env;
	while ((*env)->next)
	{
		if (ft_strcmp((*env)->n_v, (*env)->next->n_v) > 0)
		{
			sp = (*env)->n_v;
			(*env)->n_v = (*env)->next->n_v;
			(*env)->next->n_v = sp;
			(*env) = cur;
		}
		else
			(*env) = (*env)->next;
	}
	(*env) = cur;
	return (*env);
}
