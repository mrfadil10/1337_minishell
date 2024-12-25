/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 22:22:00 by stemsama          #+#    #+#             */
/*   Updated: 2023/08/13 18:48:04 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fd1_fd2_norm3(t_data *node2, int *fd2, int a)
{
	if ((node2->next->t_type == SUPERIOR \
		|| node2->next->t_type == ADD) && (a == 0))
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
		a = 1;
		return (1);
	}
	return (0);
}

void	go_to_execve_nprm3(char	**all_path, char **cmd, char **env)
{
	int		i;

	i = 0;
	while (all_path[i])
	{
		all_path[i] = ft_mystrjoin(all_path[i], "/");
		all_path[i] = ft_mystrjoin(all_path[i], cmd[0]);
		if (access(all_path[i], F_OK | X_OK) == 0)
			break ;
		if (all_path[++i] == NULL)
		{
			ft_putstr_fd("minishell: command not found\n", 2);
			exit (127);
		}
	}
	{
		if (execve(all_path[i], cmd, env) < 0)
		{
			perror("Minishell ");
			exit (1);
		}
	}
}

int	choice_norm1(int p, t_env *lst_env, char **env, t_data	*data)
{
	(void) lst_env;
	choice_norm9(data);
	if (hrdc(data, &data->in, env) == 1)
		return (1);
	expand(data, lst_env);
	if (data->av)
	{
		handle_quotes(data);
		data->commands = data->av[0];
	}
	if (p >= 400)
	{
		ft_putstr_fd("fork: Resource temporarily unavailable\n", 2);
		return (1);
	}
	return (0);
}

void	choice_norm2(t_data *node, int *fd1, int *fd2)
{
	if (*fd2 != -2)
		out_redirection(node, *fd2);
	if (*fd1 != -2)
		in_redirection(node, *fd1);
}

int	choice_norm3(t_data *node, int outt, int inn)
{
	if (node->out != -2 && (node->out != ERROR))
	{
		if (dup2(outt, 1) == -1)
		{
			printf("Erreur lors de la redirection out\n");
			return (1);
		}
		close(node->out);
	}
	if (node->in != -2 && (node->in != ERROR))
	{
		if (dup2(inn, 0) == -1)
		{
			printf("Erreur lors de la redirection out\n");
			return (1);
		}
		close(node->in);
	}
	return (0);
}
