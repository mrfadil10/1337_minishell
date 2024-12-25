/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 21:34:02 by stemsama          #+#    #+#             */
/*   Updated: 2023/08/13 18:36:42 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	go_to_export_norm(t_env **exp, t_env **env, char *argv)
{
	if (!check_existe(exp, passe_sep(argv, '+'), 0))
	{
		ft_lstadd_back2(exp, ft_lstnew_ind2(passe_sep(argv, '+')));
		ft_lstadd_back2(env, ft_lstnew_ind2(passe_sep(argv, '+')));
		return (0);
	}
	else
	{
		plus_equal_exist(exp, argv);
		plus_equal_exist_env(env, argv);
	}
	return (1);
}

void	go_to_execve_norm1(t_env **lst_env, char **cmd, char **env)
{
	char	*path;
	char	**all_path;

	path = get_value(lst_env, "PATH");
	if (path == NULL || ft_strcmp(cmd[0], "") == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit (127);
	}
	all_path = ft_mysplit(path, ':');
	go_to_execve_nprm3(all_path, cmd, env);
}

void	go_to_execve_norm2(char **cmd, char **env)
{
	if (cmd && cmd[0])
	{
		if (cmd[0])
		{
			if (execve(cmd[0], cmd, env) < 0)
			{
				perror("Minishell ");
				exit (1);
			}
		}
	}
}

int	fd1_fd2_norm1(t_data *node2, int *fd2, int a)
{
	if ((node2->t_type == SUPERIOR || node2->t_type == ADD) && (a == 0))
	{
		if (*fd2 != -2)
			close(*fd2);
		if (node2->next->av[0])
		{
			*fd2 = open_file(node2, node2->next->av[0], NULL);
			node2->next->t_type = FILEE;
		}
		else
		{
			ft_putstr_fd("minishell: ambiguous redirect\n", 2);
			return (-2);
		}
	}
	return (0);
}

int	fd1_fd2_norm2(t_data *node2, int *fd2)
{
	if (node2->t_type == PIPE && (node2->next->t_type == SUPERIOR \
		|| node2->next->t_type == ADD))
	{
		if (*fd2 != -2)
			close(*fd2);
		if (node2->next->next->av[0])
		{
			*fd2 = open_file(node2, node2->next->next->av[0], NULL);
			node2->next->next->t_type = FILEE;
		}
		else
		{
			ft_putstr_fd("minishell: ambiguous redirect\n", 2);
			return (-2);
		}
	}
	return (0);
}
