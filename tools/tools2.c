/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 23:35:48 by stemsama          #+#    #+#             */
/*   Updated: 2023/08/13 20:50:42 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builting(char **cmd)
{
	if (cmd && cmd[0] && cmd[1] && (!ft_strcmp(cmd[0], "env")))
		return (0);
	if (cmd && cmd[0])
	{
		if (ft_strcmp(cmd[0], "echo") == 0 || ft_strcmp(cmd[0], "cd") == 0
			|| ft_strcmp(cmd[0], "pwd") == 0 || ft_strcmp(cmd[0], "export") == 0
			|| ft_strcmp(cmd[0], "unset") == 0 \
			|| (ft_strcmp(cmd[0], "env")) == 0
			|| ft_strcmp(cmd[0], "exit") == 0)
			return (1);
	}
	return (0);
}

int	go_to_builtin(char **cmd, t_env *lst_env, t_env *lst_exp)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
		g_data.exit = execute_echo(++cmd, lst_env);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		g_data.exit = execute_cd(&lst_env, cmd);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		g_data.exit = execute_pwd(&lst_env);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		g_data.exit = execute_unset(lst_env, lst_exp, ++cmd);
	else if (ft_strcmp(cmd[0], "env") == 0)
		g_data.exit = execute_env(&lst_env, cmd);
	else if (ft_strcmp(cmd[0], "export") == 0)
		g_data.exit = execute_export(&lst_exp, &lst_env, cmd);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		g_data.exit = execute_exit(cmd);
	return (-5);
}

int	go_to_execve(t_env **lst_env, char **cmd, char **env)
{
	int		i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd && cmd[i])
			cmd[i] = ft_mystrtrim(cmd[i], "\"'"); // SuS
	}

	if (cmd && cmd[0])
	{
		if (ft_ispath(cmd[0]) == 0)
		{
			go_to_execve_norm1(lst_env, cmd, env);
		}
	}
	go_to_execve_norm2(cmd, env);
	exit (1);
}

char	*passe_sep2(char *argv, char sep)
{
	char	*new;
	int		i;
	int		j;
	int		nbr_sep;

	nbr_sep = 0;
	i = 0;
	j = -1;
	while (argv[i])
	{
		if (argv[i] == sep)
			nbr_sep++;
		i++;
	}
	new = ft_malloc(sizeof(char) * ft_strlen(argv) + 1 - nbr_sep);
	if (!new)
		return (NULL);
	i = 0;
	while (argv[++j])
	{
		if (argv[j] != sep)
			new[i++] = argv[j];
	}
	new[i] = '\0';
	return (new);
}

char	*passe_sep(char *argv, char sep)
{
	char	*new;
	int		i;
	int		j;
	int		check;

	check = 1;
	i = 0;
	j = -1;
	new = ft_malloc(sizeof(char) * ft_strlen(argv));
	if (!new)
		return (NULL);
	while (argv[++j])
	{
		if (argv[j] != sep)
			new[i++] = argv[j];
		if (argv[j] == sep && check == 0)
		{
			new[i] = argv[j];
			i++;
		}
		if (argv[j] == sep)
			check = 0;
	}
	return (new);
}
