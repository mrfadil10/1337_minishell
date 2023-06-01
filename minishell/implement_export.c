/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 00:17:23 by stemsama          #+#    #+#             */
/*   Updated: 2023/05/06 16:06:13 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	*execute_export(t_env **env, char **argv)
{
	t_env	*cur;
	int		i;

	cur = *env;
	if (argv[1] == NULL)
	{
		while (cur)
		{
			printf("declare -x %s", get_name(cur->n_v));
			if (cur->value)
				printf("=\"%s\"\n", get_value1(cur->n_v) + 1);
			else
				printf("=\"\"\n");
			cur = cur->next;
		}
	}
	i = 0;
	while (argv[++i])
	{
		if (pars_export(argv[i]) == 1)
			printf("minishell: export: `%s': not a valid identifier\n", argv[i]);
		else
			go_to_export(env, argv[i]);
	}
	return (0);
}

void	go_to_export(t_env **env, char *argv)
{
	(void) env;
	(void) argv;
	printf("minishell: expo\n");
	// t_env *add;
	// if (check_existe(env, argv[i]) == 0 && ft_strnstr())
		// ft_lstadd_back2(env, ft_lstnew_ind2(argv));
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
		//il ya d'autre condition
		if ((av[i] >= '0' && av[i] <= '9' && i == 0)
			|| ((av[i] >= 'z' && av[i] <= 'a') && (av[i] != '+' && av[i] != '_'))
			|| ((av[i] >= 'Z' && av[i] <= 'A') && (av[i] != '+' && av[i] != '_'))
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
