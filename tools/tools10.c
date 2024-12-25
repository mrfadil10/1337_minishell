/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools10.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:04:48 by stemsama          #+#    #+#             */
/*   Updated: 2023/08/13 16:39:47 by mfadil           ###   ########.fr       */
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

void	go_to_home(t_env **env)
{
	char	*pwd;

	pwd = get_value(env, "PWD");
	if (!pwd)
		return ;
	upd_oldpwd(env, pwd);
}

char	*get_value(t_env **env, char *name)
{
	t_env	*value2;

	value2 = *env;
	while (value2 && ft_strcmp(value2->name, name))
		value2 = value2->next;
	if (value2)
	{
		if ((value2 && value2->value && (value2->tag == 0)))
			return (value2->value);
	}
	return (NULL);
}

char	*get_path_norm1(t_env **env, char **cmd)
{
	char	*path;

	path = NULL;
	if (!ft_strcmp(cmd[0], "cd") && (!ft_strcmp(cmd[1], "-")))
	{
		path = get_value(env, "OLDPWD");
		if (!path)
		{
			upd_oldpwd(env, path);
			if (!path)
				return (NULL);
			g_data.exit = 1;
			return (NULL);
		}
		if (path)
			path++;
		ft_putstr_fd(path, 1);
		ft_putstr_fd("\n", 1);
	}
	else
		path = cmd[1];
	return (path);
}

int	upd_oldpwd_norm1(t_env **env, char *pwd)
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
			cur->value = type_strdup("=");
	}
	if (!pwd)
		return (ERROR);
	return (0);
}
