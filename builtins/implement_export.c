/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 00:17:23 by stemsama          #+#    #+#             */
/*   Updated: 2023/08/13 16:02:53 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	affiche_export(t_env **env)
{
	t_env	*cur;

	cur = *env;
	while (cur)
	{
		printf("declare -x %s", get_name(cur->n_v));
		if (cur->value)
			printf("=\"%s\"", get_value1(cur->n_v) + 1);
		else if (ft_strchr(cur->n_v, '='))
			printf("=\"\"");
		printf("\n");
		cur = cur->next;
	}
}

int	execute_export(t_env **exp, t_env **env, char **argv)
{
	t_env	*cur;
	t_env	**expp;
	int		i;
	int		status;

	cur = *exp;
	expp = exp;
	status = 0;
	execute_export_norm_1(argv, cur);
	i = 0;
	while (argv[++i])
	{
		if (pars_export(argv[i]) == 1)
		{
			status = 42;
			printf("minishell: export: `%s': not a valid identifier\n", argv[i]);
		}
		else
			go_to_export(exp, env, argv[i]);
		exp = expp;
	}
	if (status == 42)
		return (1);
	return (0);
}

int	go_to_export(t_env **exp, t_env **env, char *argv)
{
	t_env	*tmp;

	tmp = *exp;
	if (ft_strchr(argv, '+') != 0 && \
	ft_strncmp((ft_strchr(argv, '+') + 1), "=", 1) == 0)
	{
		if (go_to_export_norm(exp, env, argv) == 0)
			return (0);
	}
	else if (!check_existe(exp, argv, 0))
	{
		ft_lstadd_back2(exp, ft_lstnew_ind2(argv));
		if (ft_strchr(argv, '=') != 0)
			ft_lstadd_back2(env, ft_lstnew_ind2(argv));
	}
	else if (ft_strchr(argv, '=') != 0)
	{
		equal(exp, argv);
		equal_env(env, argv);
	}
	return (0);
}

int	check_existe(t_env **env, char *new, int flag)
{
	t_env	*tmp;

	if (env == NULL)
		return (0);
	(void) flag;
	tmp = *env;
	while (tmp != NULL)
	{
		if (!ft_strcmp(get_name(new), tmp->name))
		{
			if (tmp->tag == 1)
				return (2);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	pars_export(char *av)
{
	int	a[2];
	int	i;

	i = 0;
	a[0] = 0;
	a[1] = 0;
	if ((av[0] > 64 && av[0] < 91)
		|| (av[0] > 96 && av[0] <= 122) || av[0] == '_')
		a[0] = 1;
	while (av[i] && av[i] != '=')
	{
		if ((av[i] >= '0' && av[i] <= '9' && i == 0) || ((av[i] >= 'z'
					&& av[i] <= 'a') && (av[i] != '+' && av[i] != '_'))
			|| ((av[i] >= 'Z' && av[i] <= 'A') && \
			(av[i] != '+' && av[i] != '_'))
			|| (av[i] == '+' && av[i + 1] != '='))
		{
			a[1] = 1;
			break ;
		}
		i++;
	}
	if (a[0] == 0 || a[1] == 1)
		return (1);
	return (0);
}
