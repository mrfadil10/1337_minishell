/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:35:42 by stemsama          #+#    #+#             */
/*   Updated: 2023/07/12 21:59:34 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_globv	g_data;

int	main(int argc, char **argv, char **env)
{
	t_data	*lst_env;
	t_data	*parameter;
	char	*line;

	(void) argc;
	(void) argv;
	parameter = NULL;
	lst_env = creat_env(env);
	lst_env = sort_env(&lst_env);
	sig_nals();
	while (1)
	{
		line = readline("minishell$");
		parameter->commands = ft_split(line, ' ');
		parsing(parameter->commands, env);
		add_history(line);
		if (is_builting(parameter->commands))
			go_to_builting(parameter->commands, lst_env);
		else
			go_to_execve(&lst_env, parameter->commands, env);
	}
	return (0);
}
