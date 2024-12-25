/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:40:57 by stemsama          #+#    #+#             */
/*   Updated: 2023/08/13 17:04:15 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	choice_norm4(t_data *node, t_env *lst_env, char **env)
{
	g_data.pid = fork();
	if (g_data.pid == -1)
	{
		perror("fork");
		return (1);
	}
	else if (g_data.pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		choice_norm2(node, &node->in, &node->out);
		go_to_execve(&lst_env, node->av, env);
	}
	if (g_data.pid != -1)
		waitpid(g_data.pid, &g_data.exit_status, 0);
	while (wait(NULL) != -1)
		;
	if (choice_norm3(node, g_data.outt, g_data.inn) == 1)
		return (1);
	return (0);
}

int	choice_norm5(t_data *node, t_env *lst_env, char **env, t_env *lst_exp)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (node->in != -2)
	{
		dup2(node->in, 0);
		close(node->in);
	}
	if (node->out != -2)
	{
		dup2(node->out, 1);
		close(node->out);
	}
	if (g_data.p != 0)
	{
		close(node->pipe[0]);
		close(node->pipe[1]);
		if (g_data.old)
			close(g_data.old->in);
	}
	if (is_builting(node->av))
		g_data.exit_status = go_to_builtin(node->av, lst_env, lst_exp);
	else
		g_data.exit = go_to_execve(&lst_env, node->av, env);
	exit (g_data.exit);
}

int	choice_norm6(t_data *node, t_env *lst_env, char **env, t_env *lst_exp)
{
	g_data.pid = fork();
	if (g_data.pid == -1)
	{
		perror("fork");
		return (1);
	}
	else if (g_data.pid == 0)
		choice_norm5(node, lst_env, env, lst_exp);
	if (g_data.p != 0)
		close(node->pipe[1]);
	if (g_data.old != NULL)
		close(g_data.old->pipe[0]);
	g_data.old = node;
	if (node->next)
		node = next_node2(node);
	else
		return (2);
	g_data.p--;
	return (0);
}

void	choice_norm7(t_data *node)
{
	if (g_data.p != 0)
		pipe(node->pipe);
	if (g_data.old != NULL)
		node->in = g_data.old->pipe[0];
	if (g_data.p != 0)
		node->out = node->pipe[1];
}

void	choice_norm8(t_data *node)
{
	if (g_data.p != 0)
		close(node->pipe[1]);
	if (g_data.old != NULL)
		close(g_data.old->pipe[0]);
	g_data.old = node;
}
