/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 16:18:47 by stemsama          #+#    #+#             */
/*   Updated: 2023/08/13 17:22:44 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//int	check_unset(t_env *env, char **cmd)
//{
//	if (!cmd[1] || !ft_strcmp("~", cmd[1]))
//	{
//		while (env != NULL)
//		{
//			if (!ft_strcmp(get_name("HOME"), env->name))
//			{
//				if (env->tag == 1)
//					return (1);
//				else
//					return (0);
//			}
//			env = env->next;
//		}
//	}
//	return (0);
//}

int	execute_cd(t_env **env, char **cmd)
{
	char	*path;

	path = get_path(env, cmd);
	if (path == NULL)
	{
		go_to_home(env);
		return (1);
	}
	if (!path)
		return (1);
	if (check_unset(*env, cmd) == 1)
	{
		printf("Path not valid\n");
		return (1);
	}
	if (chdir(path) == -1)
	{
		perror("Minishell ");
		return (1);
	}
	go_to_home(env);
	return (0);
}

char	*get_path(t_env **env, char **cmd)
{
	char	*path;

	path = NULL;
	if (cmd == NULL)
		return (NULL);
	if (*cmd == NULL)
		return (NULL);
	if ((!ft_strcmp(cmd[0], "cd") && (!ft_strcmp(cmd[1], "~")))
		|| (!ft_strcmp(cmd[0], "cd") && (cmd[1] == NULL)))
	{
		path = get_value(env, "HOME");
		if (!path)
		{
			printf("minishell: cd: HOME not set\n");
			g_data.exit = 1;
		}
		if (path)
			path++;
	}
	else
		path = get_path_norm1(env, cmd);
	return (path);
}

//char	*get_value(t_env **env, char *name)
//{
//	t_env	*value2;

//	value2 = *env;
//	while (value2 && ft_strcmp(value2->name, name))
//		value2 = value2->next;
//	if (value2)
//	{
//		if ((value2 && value2->value && (value2->tag == 0)))
//			return (value2->value);
//		if (((value2 && value2->value && (!ft_strcmp(value2->name, "OLDPWD")))))
//			return (NULL);
//	}
//	return (NULL);
//}

//void	go_to_home(t_env **env)
//{
//	char	*pwd;
//	char	*oldpwd;

//	pwd = get_value(env, "PWD");
//	if (!pwd)
//		return ;
//	oldpwd = get_value(env, "OLDPWD");
//	if (!oldpwd)
//		return ;
//	upd_oldpwd(env, pwd);
//}

int	upd_oldpwd(t_env **env, char *pwd)
{
	t_env	*cur;

	if (upd_oldpwd_norm1(env, pwd) == ERROR)
		return (ERROR);
	cur = *env;
	pwd = getcwd(NULL, 0);
	while (cur && ft_strcmp(cur->name, "PWD"))
		cur = cur->next;
	if (!pwd)
	{
		g_data.exit = 1;
		printf("cd: error retrieving current directory: getcwd:\
 cannot access parent directories: No such file or directory\n");
		cur->value = ft_mystrjoin(get_value(env, "PWD"), "/..");
		ft_free(pwd);
		return (1);
	}
	if (cur && cur->value)
	{
		cur->value = NULL;
		cur->value = ft_mystrjoin("=", pwd);
	}
	ft_free(pwd);
	return (0);
}
