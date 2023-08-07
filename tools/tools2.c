/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 23:35:48 by stemsama          #+#    #+#             */
/*   Updated: 2023/08/07 19:40:47 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builting(char **cmd)
{
	if (cmd && cmd[0])
	{
		if (ft_strcmp(cmd[0], "echo") == 0 || ft_strcmp(cmd[0], "cd") == 0
			|| ft_strcmp(cmd[0], "pwd") == 0 || ft_strcmp(cmd[0], "export") == 0
			|| ft_strcmp(cmd[0], "unset") == 0 || ft_strcmp(cmd[0], "env") == 0
			|| ft_strcmp(cmd[0], "exit") == 0)
			return (1);
	}
	return (0);
}

void	go_to_builting(char **cmd, t_env *lst_env, t_env *lst_exp)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
		execute_echo(++cmd);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		execute_cd(&lst_env, cmd);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		execute_pwd(&lst_env);
	else if (ft_strcmp(cmd[0], "export") == 0)
		execute_export(&lst_exp, &lst_env, cmd);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		execute_unset(lst_env, lst_exp, ++cmd);
	else if (ft_strcmp(cmd[0], "env") == 0)
		execute_env(&lst_env);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		execute_exit(++cmd);
}

int ft_ispath(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
		return (0);
}

void	go_to_execve(t_data *data, t_env **lst_env, char **cmd, char **env)
{
	char	*path;
	char	**all_path;
	int		i;
	// int		pid;

	(void) data;
	i = 0;
	if(ft_ispath(cmd[0]) == 0)
	{
		path = get_value(lst_env, "PATH");
		all_path = ft_split(path, ':');
		while (all_path[i])
		{
			all_path[i] = ft_strjoin(all_path[i], "/");
			all_path[i] = ft_strjoin(all_path[i], cmd[0]);
			if (access(all_path[i], F_OK) == 0)
				break;
			i++;
			if(all_path[i] == NULL)
			{
				printf("command not found\n");
				exit(1);
			}
		}
		if (all_path[i])
		{
			if (execve(all_path[i], cmd, env) < 0)
			{
				perror("Minishell:");
				exit(127);
			}
		}
	}
	if (cmd[0])
	{
		if (execve(cmd[0], cmd, env) < 0)
		{
			perror("Minishell:");
			exit(127);
		}
	}
}

char *passe_sep(char *argv, char sep)
{
	char	*new;
	int		i;
	int		j;
	int		check;

	check = 1;
	i = 0;
	j = -1;
	new = malloc(sizeof(char) * ft_strlen(argv));
	while (argv[++j])
	{
		if (argv[j] != sep)
		{
			new[i] = argv[j];
			i++;
		}
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
