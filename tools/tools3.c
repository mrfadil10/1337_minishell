/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 02:13:22 by stemsama          #+#    #+#             */
/*   Updated: 2023/08/13 16:28:04 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	plus_equal_exist(t_env **exp, char *argv)
{
	t_env	**tmp;

	tmp = exp;
	while ((*tmp) != NULL)
	{
		if (!ft_strcmp(get_name(passe_sep(argv, '+')), (*tmp)->name))
		{
			if (ft_strchr((*tmp)->value, '='))
				(*tmp)->value = ft_mystrjoin((*tmp)->value \
				+ 1, get_value1(argv) + 1);
			else
				(*tmp)->value = ft_mystrjoin((*tmp)->value,
						get_value1(argv) + 1);
			(*tmp)->n_v = ft_mystrjoin((*tmp)->name, type_strdup("="));
			(*tmp)->n_v = ft_mystrjoin((*tmp)->n_v, (*tmp)->value);
		}
		*tmp = (*tmp)->next;
	}
}

void	plus_equal_exist_env(t_env **env, char *argv)
{
	t_env	**tmp;

	tmp = env;
	while ((*tmp) != NULL)
	{
		if (!ft_strcmp(get_name(passe_sep(argv, '+')), (*tmp)->name))
		{
			(*tmp)->value = ft_mystrjoin((*tmp)->value, get_value1(argv) + 1);
			(*tmp)->n_v = ft_mystrjoin((*tmp)->name, (*tmp)->value);
			return ;
		}
		*tmp = (*tmp)->next;
	}
}

void	equal(t_env **exp, char *argv)
{
	t_env	**tmp;

	tmp = exp;
	if (tmp == NULL)
		return ;
	while ((*tmp) != NULL)
	{
		if (!ft_strcmp(get_name(argv), (*tmp)->name))
		{
			(*tmp)->value = get_value1(argv) + 1;
			(*tmp)->n_v = argv;
			(*tmp)->tag = 0;
			return ;
		}
		(*tmp) = (*tmp)->next;
	}
}

void	equal_env(t_env **exp, char *argv)
{
	t_env	**tmp;

	tmp = exp;
	if (tmp == NULL)
		return ;
	while ((*tmp) != NULL)
	{
		if (!ft_strcmp(get_name(argv), (*tmp)->name))
		{
			(*tmp)->value = get_value1(argv);
			(*tmp)->n_v = argv;
			(*tmp)->tag = 0;
			return ;
		}
		(*tmp) = (*tmp)->next;
	}
}
