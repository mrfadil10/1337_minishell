/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 02:13:22 by stemsama          #+#    #+#             */
/*   Updated: 2023/07/16 14:07:03 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void plus_equal_exist(t_env **exp, char *argv)
{
	while ((*exp) != NULL)
	{
		if (!ft_strcmp(get_name(passe_sep(argv, '+')), (*exp)->name))
		{
			if (ft_strchr((*exp)->value, '='))
				(*exp)->value = ft_strjoin((*exp)->value + 1, get_value1(argv) + 1);
			else
				(*exp)->value = ft_strjoin((*exp)->value, get_value1(argv) + 1);
			(*exp)->n_v = ft_strjoin((*exp)->name, ft_strdup("="));
			(*exp)->n_v = ft_strjoin((*exp)->n_v, (*exp)->value);
			return ;
		}
		*exp = (*exp)->next;
	}
}

void plus_equal_exist_env(t_env **env, char *argv)
{
	while ((*env) != NULL)
	{
		if (!ft_strcmp(get_name(passe_sep(argv, '+')), (*env)->name))
		{
			(*env)->value = ft_strjoin((*env)->value, get_value1(argv) + 1);
			(*env)->n_v = ft_strjoin((*env)->name, (*env)->value);
			return ;
		}
		*env = (*env)->next;
	}
}

void equal(t_env **exp, char *argv)
{
	while ((*exp) != NULL)
	{
		if (!ft_strcmp(get_name(argv), (*exp)->name))
		{
			(*exp)->value = get_value1(argv) + 1;
			(*exp)->n_v = argv;
			return ;
		}
		(*exp) = (*exp)->next;
	}
}

void equal_env(t_env **exp, char *argv)
{
	while ((*exp) != NULL)
	{
		if (!ft_strcmp(get_name(argv), (*exp)->name))
		{
			(*exp)->value = get_value1(argv);
			(*exp)->n_v = argv;
			return ;
		}
		(*exp) = (*exp)->next;
	}
}
