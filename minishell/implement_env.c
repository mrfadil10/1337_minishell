/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 23:13:51 by stemsama          #+#    #+#             */
/*   Updated: 2023/05/06 15:49:59 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*execute_env(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		printf("%s", tmp->name);
		if (tmp->value)
			printf("%s\n", tmp->value);
		tmp = tmp->next;
	}
	return (*env);
}

t_env	*creat_env(char **env)
{
	int		i;
	t_env	*lst;

	i = -1;
	lst = NULL;
	while (env[++i])
		ft_lstadd_back2(&lst, ft_lstnew_ind2(env[i]));
	return (lst);
}
