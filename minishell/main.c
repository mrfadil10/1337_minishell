/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:35:42 by stemsama          #+#    #+#             */
/*   Updated: 2023/05/29 11:10:06 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_env	*lst_env;
	t_data	*parameter;
	char	*line;
	char	**cmd;

	(void) argc;
	(void) argv;
	lst_env = creat_env(env);
	lst_env = sort_env(&lst_env);
	sig_nals();
	while (1)
	{
		line = readline("minishell$");
		parameter->commands = ft_split(line, ' ');
		parsing(parameter);
		add_history(line);
		if (is_builting(parameter->commands))
			go_to_builting(parameter->commands, lst_env);
		else
			go_to_execve(&lst_env, parameter->commands, env);
	}
	return (0);
}
