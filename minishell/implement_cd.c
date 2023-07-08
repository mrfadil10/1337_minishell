/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 16:18:47 by stemsama          #+#    #+#             */
/*   Updated: 2023/06/06 22:58:40 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_cd(t_data **env, char **argv)
{
	char	*path;

	path = get_path(env, argv);
	if (!path)
		return (ERROR);
	if (chdir("/Users/stemsama") == -1)
	{
		//probleme 2 : path non valid ? !! (valide -> "path" (../..))
		printf("minishell: cd: %s : No such file or directory", path);
		return (ERROR);
	}
	go_to_home(env);
	return (0);
}

char	*get_path(t_data **env, char **argv)
{
	char	*path;

	path = NULL;
	//we have a probleme in ~  (replace with k sera travailler)
	if ((!ft_strcmp(argv[1], "cd") && (!ft_strcmp(argv[2], "~")))
		|| (!ft_strcmp(argv[1], "cd") && (argv[2] == NULL)))
	{
		// printf("\n----------->>minishell: cd:HOME not set\n");
		path = get_value(env, "HOME");
		if (!path)
			printf("minishell: cd: HOME not set");
	}
	else if (!ft_strcmp(argv[1], "cd") && (!ft_strcmp(argv[2], "-")))
	{
		// printf("\n----------->>minishell:\n");
		path = get_value(env, "OLDPWD");
		if (!path)
			printf("minishell: cd: HOME not set");
	}
	else
		path = argv[1];
	return (path);
}

char	*get_value(t_data **env, char *name)
{
	t_data	*value2;

	value2 = *env;
	while (value2 && ft_strcmp(value2->name, name))
		value2 = value2->next;
	if (value2 && value2->value)
		return (value2->value);
	return (NULL);
}

void	go_to_home(t_data **env)
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

int	upd_oldpwd(t_data **env, char *pwd)
{
	t_data	*cur;

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
		return (ERROR);//ou cas ou pwd nexiste pas on a besoin de changer oldpwd.
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
