/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:35:42 by stemsama          #+#    #+#             */
/*   Updated: 2023/08/08 15:39:19 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_globv	g_data;

void	check_empty_line(char *line)
{
	g_data.heredoc = 1;
	type_lstadd_back(line, 1);
	if (line == NULL)
	{
		printf("mininshell$ exit\n");
		free_all(0);
		exit(g_data.exit);
	}
}

void	exp_and_exec(t_data *data, t_env *lst_env, t_env *lst_exp, char **env)
{
	expand(data, lst_env);
	if (data->av)
	{
		handle_quotes(data);
		data->commands = data->av[0];
	}
	choice(data, lst_env, lst_exp, env);
}

int	main(int argc, char **argv, char **env)
{
	t_env	*lst_env;
	t_env	*lst_exp;
	t_data	*data;
	char	*line;

	(void) argv;
	(void) argc;
	if (isatty(STDIN_FILENO) == 0)
		return (0);
	lst_env = creat_env(env);
	lst_exp = creat_env(env);
	lst_exp = sort_env(&lst_exp);
	rl_catch_signals = 0;
	sig_nals();
	while (1)
	{
		g_data.heredoc = 0;
		line = readline("minishell$ ");

		if (!line)
			return (ft_putstr_fd("exit\n", 1), exit(0), 1);
		add_history(line);
		data = parsing(line, env);
		if (!data)
			continue ;
		exp_and_exec(data, lst_env, lst_exp, env);
	}
	return (0);
}
