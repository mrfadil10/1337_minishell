/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:35:42 by stemsama          #+#    #+#             */
/*   Updated: 2023/08/03 20:25:45 by mfadil           ###   ########.fr       */
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
	int		i;
	int		j;

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
		if (!line)
			return (ft_putstr_fd("exit\n", 1), exit(0), 1);
		add_history(line);
		cmd = ft_split(line, ' ');
		data = parsing(line, env);
		if (!data)
			continue ;
		expand(data, env);
		i = 0;
		while (data->av[i])
		{
			j = 0;
			while (data->av[i][j])
			{
				if (data->av[i][j] == '\'' || data->av[i][j] == '"')
				{
					if (part_of_delete_quote(data, i, &j))
						break ;
				}
				else
					j++;
			}
			i++;
		}
		data->commands = data->av[0];
		if (is_builting(data->av))
			go_to_builting(data->av, lst_env, lst_exp);
		else
			go_to_execve(&lst_env, data->av, env);
	}
	return (0);
}
