/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 01:16:43 by stemsama          #+#    #+#             */
/*   Updated: 2023/08/13 20:31:17 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	go_to_unset(t_env *env, t_env *exp, char *cmd)
{
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (!ft_strcmp(get_name(cmd), tmp->name))
		{
			tmp->tag = 1;
			tmp->tag3 = 1;
			break ;
		}
		tmp = tmp->next;
	}
	tmp = exp;
	while (tmp != NULL)
	{
		if (!ft_strcmp(get_name(cmd), tmp->name))
		{
			tmp->tag = 1;
			tmp->tag3 = 1;
			break ;
		}
		tmp = tmp->next;
	}
	return (0);
}

int	pars_unset(char *av)
{
	int	a[2];
	int	i;

	i = 0;
	a[0] = 0;
	a[1] = 0;
	if ((av[0] > 64 && av[0] < 91)
		|| (av[0] > 96 && av[0] <= 122) || av[0] == '_')
		a[0] = 1;
	while (av[i])
	{
		if ((av[i] >= '0' && av[i] <= '9') || (av[i] >= 'a' && av[i] <= 'z') || av[i] == '_' || (av[i] >= 'A' && av[i] <= 'Z'))
			i++;
		else
		{
			a[1] = 1;
			break ;
		}
	}
	if (a[0] == 0 || a[1] == 1)
		return (1);
	return (0);
}

int	execute_unset(t_env *env, t_env *exp, char **cmd)
{
	int	i;
	int	status;

	i = -1;
	status = 0;
	while (cmd[++i])
	{
		if (pars_unset(cmd[i]) == 1)
		{
			printf("minishell: unset: `%s': not a valid identifier\n", cmd[i]);
			status = 42;
		}
		else
			status = go_to_unset(exp, env, cmd[i]);
	}
	if (status == 42)
		return (1);
	return (0);
}
