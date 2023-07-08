/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 23:13:51 by stemsama          #+#    #+#             */
/*   Updated: 2023/06/06 22:59:16 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*execute_env(t_data **env)
{
	t_data	*tmp;

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

t_data	*creat_env(char **env)
{
	int		i;
	t_data	*lst;

	i = -1;
	lst = NULL;
	while (env[++i])
		ft_lstadd_back2(&lst, ft_lstnew_ind2(env[i]));
	return (lst);
}
