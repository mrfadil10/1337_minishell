/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 23:13:51 by stemsama          #+#    #+#             */
/*   Updated: 2023/08/13 15:54:51 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_env(t_env **env, char **cmd)
{
	t_env	*tmp;

	if (cmd[1])
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(" No such file or directory\n", 2);
		return (127);
	}
	tmp = *env;
	while (tmp)
	{
		if (tmp->tag == 0)
		{
			printf("%s", tmp->name);
			if (tmp->value)
				printf("%s\n", tmp->value);
		}
		tmp = tmp->next;
	}
	return (0);
}

t_env	*creat_env(char **env)
{
	int		i;
	t_env	*lst;

	i = -1;
	lst = NULL;
	while (env[++i])
		ft_lstadd_back2(&lst, ft_lstnew_ind2(env[i]));
	lst = sort_env(&lst);
	return (lst);
}

t_env	*ft_lstnew_ind3(char *content)
{
	t_env	*b;

	b = (t_env *)ft_malloc(sizeof(t_env));
	if (!b)
		return (NULL);
	b->name = get_name(content);
	b->value = get_value1(content);
	b->n_v = content;
	b->tag = 1;
	b->tag2 = 1;
	b->next = NULL;
	return (b);
}

t_env	*creat_env2(char **env)
{
	int		i;
	t_env	*lst;

	(void) env;
	i = -1;
	lst = NULL;
	ft_lstadd_back2(&lst, ft_lstnew_ind3("USER=stemsama"));
	ft_lstadd_back2(&lst, \
	ft_lstnew_ind3("PWD=/Users/stemsama/Desktop/last_minishell"));
	return (lst);
}
