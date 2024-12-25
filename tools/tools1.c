/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 23:35:48 by stemsama          #+#    #+#             */
/*   Updated: 2023/08/13 17:21:39 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back2(t_env **lst, t_env *new)
{
	t_env	*tmp;

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

t_env	*ft_lstnew_ind2(char *content)
{
	t_env	*b;

	b = (t_env *)ft_malloc(sizeof(t_env));
	if (!b)
		return (NULL);
	b->name = get_name(content);
	b->value = get_value1(content);
	b->n_v = content;
	b->tag = 0;
	b->next = NULL;
	return (b);
}

char	*get_name(char *str)
{
	char	*name;

	name = ft_strchr(str, '=');
	if (!name)
		return (str);
	return (type_substr(str, 0, ft_strlen(str) - ft_strlen(name)));
}

char	*get_value1(char *str)
{
	return (ft_strchr(str, '='));
}

t_env	*sort_env(t_env **env)
{
	t_env	*cur;
	char	*sp;
	char	*n;
	char	*v;

	cur = *env;
	while ((*env)->next)
	{
		if (ft_strcmp((*env)->n_v, (*env)->next->n_v) > 0)
		{
			sp = (*env)->n_v;
			n = (*env)->name;
			v = (*env)->value;
			(*env)->n_v = (*env)->next->n_v;
			(*env)->name = (*env)->next->name;
			(*env)->value = (*env)->next->value;
			(*env)->next->n_v = sp;
			(*env)->next->name = n;
			(*env)->next->value = v;
			(*env) = cur;
		}
		else
			(*env) = (*env)->next;
	}
	return (cur);
}
