/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools9.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 00:56:09 by stemsama          #+#    #+#             */
/*   Updated: 2023/08/13 16:39:00 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	choice_norm9(t_data *data)
{
	g_data.outt = dup(1);
	g_data.inn = dup(0);
	g_data.p = nbr_pipe(data);
	g_data.old = NULL;
	g_data.exit_status = 0;
}

int	choice_norm10(t_env *lst_env, t_env *lst_exp, char **env)
{
	if (g_data.p == 0)
	{
		if (fd1_fd2(g_data.nd, &g_data.nd->in, &g_data.nd->out) == -2)
			return (1);
		if (is_builting(g_data.nd->av))
		{
			choice_norm2(g_data.nd, &g_data.nd->in, &g_data.nd->out);
			g_data.exit_status = go_to_builtin(g_data.nd->av, lst_env, lst_exp);
			if (choice_norm3(g_data.nd, g_data.outt, g_data.inn) == 1)
				return (1);
			return (-5);
		}
		else
		{
			if (choice_norm4(g_data.nd, lst_env, env) == 1)
				return (1);
			return (g_data.exit_status);
		}
		return (g_data.exit_status);
	}
	return (0);
}

int	choice_norm11(t_data *node, t_env *lst_env, t_env *lst_exp, char **env)
{
	while (node)
	{
		choice_norm7(node);
		if (fd1_fd2(node, &node->in, &node->out) == -2)
		{
			if (node->next)
				node = next_node2(node);
			continue ;
		}
		g_data.pid = fork();
		if (g_data.pid == -1)
		{
			perror("fork");
			return (1);
		}
		else if (g_data.pid == 0)
			choice_norm5(node, lst_env, env, lst_exp);
		choice_norm8(node);
		if (node->next)
			node = next_node2(node);
		else
			break ;
		g_data.p--;
	}
	return (0);
}

int	choice_norm12(t_env *lst_env, t_env *lst_exp, char **env)
{
	if (is_builting(g_data.nd->av))
	{
		choice_norm2(g_data.nd, &g_data.nd->in, &g_data.nd->out);
		g_data.exit_status = go_to_builtin(g_data.nd->av, lst_env, lst_exp);
		if (choice_norm3(g_data.nd, g_data.outt, g_data.inn) == 1)
			return (close(g_data.outt), close(g_data.inn), 1);
		return (close(g_data.outt), close(g_data.inn), -5);
	}
	else
	{
		if (choice_norm4(g_data.nd, lst_env, env) == 1)
			return (close(g_data.outt), close(g_data.inn), 1);
		return (close(g_data.outt), close(g_data.inn), g_data.exit_status);
	}
	return (close(g_data.outt), close(g_data.inn), g_data.exit_status);
}

int	open_file_norm1(t_data *node, char *cmd, char **name, int fd)
{
	if (node->next->t_type == SUPERIOR)
		fd = open(cmd, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (node->t_type == SUPERIOR)
		fd = open(cmd, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (node->t_type == ADD)
		fd = open(cmd, O_CREAT | O_WRONLY | O_APPEND, 0777);
	else if (node->next->t_type == ADD)
		fd = open(cmd, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (node->t_type == HRDC)
		fd = open(name[0], O_CREAT | O_RDWR, 0777);
	if (fd == -1)
	{
		perror("minisddhell");
		return (-42);
	}
	if (node->next->t_type == INFERIOR)
		fd = open(cmd, O_RDONLY);
	if (fd == -1)
	{
		perror("minishell");
		return (-42);
	}
	return (fd);
}
