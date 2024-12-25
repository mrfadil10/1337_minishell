/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:35:42 by stemsama          #+#    #+#             */
/*   Updated: 2023/08/13 16:56:16 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_globv	g_data;

int	child_status(int exit_status)
{
	int	status;

	status = WTERMSIG(exit_status);
	if (status == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", 1);
	else if (status == SIGINT)
		ft_putstr_fd("\n", 1);
	g_data.exit = WTERMSIG(status) + 128;
	return (g_data.exit);
}

int	handler_exit_status(int exit_status)
{
	if (exit_status != -5)
	{
		if (WIFEXITED(exit_status))
		{
			g_data.exit = WEXITSTATUS(exit_status);
			return (g_data.exit);
		}
		else if (WIFSIGNALED(exit_status))
		{
			g_data.exit = child_status(exit_status);
			return (g_data.exit);
		}
	}
	return (g_data.exit);
}

int	main(int argc, char **argv, char **env)
{
	t_env	*lst_env;
	t_env	*lst_exp;
	char	*line;

	if (argc != 1)
		return (0);
	(void) argv;
	line = ft_malloc(1);
	if (!line)
		ft_exit(1);
	if (isatty(STDIN_FILENO) == 0)
		return (0);
	if (env && env[0])
	{
		lst_env = creat_env(env);
		lst_exp = creat_env(env);
	}
	else
	{
		lst_exp = creat_env2(NULL);
		lst_env = creat_env2(NULL);
	}
	if (main_norm1(env, lst_env, lst_exp) == 1)
		return (1);
	return (0);
}
