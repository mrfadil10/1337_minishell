/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 00:34:58 by stemsama          #+#    #+#             */
/*   Updated: 2023/08/13 19:14:27 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file(t_data *node, char *cmd, char **name)
{
	int			fd;
	static int	num;

	num = 1;
	(void)cmd;
	fd = -2;
	if (ft_strchr(cmd, '"'))
		cmd = passe_sep2(cmd, '"');
	if (ft_strchr(cmd, '\''))
		cmd = passe_sep2(cmd, '\'');
	if (node->t_type == HRDC)
	{
		name[0] = ft_mystrjoin("/tmp/tmp_", ft_myitoa(num));
		while (access(name[0], F_OK) == 0)
		{
			num++;
			name[0] = ft_mystrjoin("/tmp/tmp_", ft_myitoa(num));
		}
	}
	fd = open_file_norm1(node, cmd, name, fd);
	if (fd == -42)
		return (-42);
	return (fd);
}

int	out_redirection(t_data *node, int fd)
{
	if (dup2(fd, 1) == -1)
	{
		perror("minishell");
		close(fd);
		return (ERROR);
	}
	close(fd);
	return (node->out);
}

int	in_redirection(t_data *node, int fd)
{
	if (dup2(fd, 0) == -1)
	{
		perror("minishell");
		close(fd);
		return (1);
	}
	close(fd);
	return (node->in);
}

int	main_norm1(char **env, t_env *lst_env, t_env *lst_exp)
{
	int		exitt;
	t_data	*data;
	char	*line;

	while (1)
	{
		rl_catch_signals = 0;
		sig_nals();
		line = ft_readline("minishell$ ");
		if (!line)
			return (ft_putstr_fd("exit\n", 2), exit(g_data.exit), 1);
		if (ft_strlen(line) != 0)
			add_history(line);
		data = parsing(line, env);
		if (!data)
			continue ;
		exitt = choice(data, lst_env, lst_exp, env);
		if (exitt != -5)
			g_data.exit = handler_exit_status(exitt);
		ft_free(line);
	}
}
