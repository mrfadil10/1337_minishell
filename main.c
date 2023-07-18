/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:35:42 by stemsama          #+#    #+#             */
/*   Updated: 2023/07/17 23:24:03 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_globv	g_data;

int	main(int argc, char **argv, char **env)
{
	t_env	*lst_env;
	t_env	*lst_exp;
	t_data	*data;
	char	*line;
	char	**cmd;

	(void) argv;
	(void) argc;
	lst_env = creat_env(env);
	lst_exp = creat_env(env);
	lst_exp = sort_env(&lst_exp);
	rl_catch_signals = 0;
	sig_nals();
	while (1)
	{
		line = readline("minishell$ ");
		cmd = ft_split(line, ' ');
		add_history(line);
		data = parsing(line, env);
		if (!data)
			continue ;
		int	i = 0;
		while (data->av[i])
		{
			data->av[i] = passe_sep2(data->av[i], '\'');
			data->av[i] = passe_sep2(data->av[i], '"');
			i++;
		}
		printf("%s\n", data->av[0]);
		printf("%s\n", data->av[1]);
		if (is_builting(cmd))
			go_to_builting(cmd, lst_env, lst_exp);
		else
			go_to_execve(&lst_env, cmd, env);
	}
	return (0);
}
