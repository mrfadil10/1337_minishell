/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 01:16:43 by stemsama          #+#    #+#             */
/*   Updated: 2023/08/06 22:45:30 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// --> HERE ls
int	execute_unset(t_env *env, t_env *exp, char **cmd)
{
	if (cmd[0])
	{
		while (env != NULL)
		{
			if (!ft_strcmp(get_name(cmd[0]), env->name))
			{
				env->tag = 1;
				break ;
			}
			env = env->next;
		}
		while (exp != NULL)
		{
			if (!ft_strcmp(get_name(cmd[0]), exp->name))
			{
				exp->tag = 1;
				return (1);
			}
			exp = exp->next;
		}
	}
	return (0);
}
