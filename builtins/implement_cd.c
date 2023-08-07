/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 16:18:47 by stemsama          #+#    #+#             */
/*   Updated: 2023/08/06 02:52:13 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_unset(t_env *env, char **cmd)
{
	if (!cmd[1] || !ft_strcmp("~", cmd[1]))
	{
		while (env != NULL)
		{
			if (!ft_strcmp(get_name("HOME"), env->name))
			{
				if (env->tag == 1)
					return (1);
				else
					return (0);
			}
			env = env->next;
		}
	}
	return (0);
}

int	execute_cd(t_env **env, char **cmd)
{
	char	*path;

	path = get_path(env, cmd);
	if (!path)
		return (ERROR);
	if (check_unset(*env, cmd) == 1)
	{
		printf("Path not valid\n");
		return (1);
	}
	if (chdir(path) == -1)
	{
		//probleme 2 : path non valid ? !! (valide -> "path" (../..))
		// printf("minishell: cd: %s : No such file or directory\n", path);
		perror("Minishell ");
		return (ERROR);
	}
	go_to_home(env);
	return (0);
}

char	*get_path(t_env **env, char **cmd)
{
	char	*path;

	path = NULL;
	//we have a probleme in ~  (replace with k sera travailler)
	if ((!ft_strcmp(cmd[0], "cd") && (!ft_strcmp(cmd[1], "~")))
		|| (!ft_strcmp(cmd[0], "cd") && (cmd[1] == NULL)))
	{
		// printf("\n----------->>minishell: cd:HOME not set\n");
		path = get_value(env, "HOME") + 1;
		if (!path)
			printf("minishell: cd: HOME not set");
	}
	else if (!ft_strcmp(cmd[0], "cd") && (!ft_strcmp(cmd[1], "-")))
	{
		path = get_value(env, "OLDPWD") + 1;
		if (!path)
			printf("minishell: cd: HOME not set");
	}
	else
		path = cmd[1];
	return (path);
}

char	*get_value(t_env **env, char *name)
{
	t_env	*value2;

	value2 = *env;
	while (value2 && ft_strcmp(value2->name, name))
		value2 = value2->next;
	if (value2 && value2->value)
		return (value2->value);
	return (NULL);
}

void	go_to_home(t_env **env)
{
	char	*pwd;
	char	*oldpwd;

	pwd = get_value(env, "PWD");
	oldpwd = get_value(env, "OLDPWD");
	if (!oldpwd)
		return ;
	// printf("\nOLDPWD	<<----------->> %s\n", get_value(env, "OLDPWD"));
	// printf("PWD	<<----------->> %s\n", get_value(env, "PWD"));
	upd_oldpwd(env, pwd);
	// printf("OLDPWD	<<----------->> %s\n", get_value(env, "OLDPWD")); 
	// printf("PWD	<<----------->> %s\n", get_value(env, "PWD"));
}

int	upd_oldpwd(t_env **env, char *pwd)
{
	t_env	*cur;

	cur = *env;
	while (cur && ft_strcmp(cur->name, "OLDPWD"))
		cur = cur->next;
	if (cur && cur->value)
	{
		cur->value = NULL;
		if (pwd)
			cur->value = pwd;
		else
			cur->value = ft_strdup("=");
	}
	if (!pwd)
		return (ERROR);//ou cas ou pwd n'existe pas on a besoin de changer oldpwd.
	cur = *env;
	pwd = getcwd(NULL, 0);
	while (cur && ft_strcmp(cur->name, "PWD"))
		cur = cur->next;
	if (cur && cur->value)
	{
		cur->value = NULL;
		cur->value = ft_strjoin("=", pwd);
	}
	return (0);
}
