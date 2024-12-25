/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_pwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 23:13:48 by stemsama          #+#    #+#             */
/*   Updated: 2023/08/13 16:20:59 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_pwd(t_env **env)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		if (get_value(env, "PWD"))
		{
			if (ft_strncmp(get_value(env, "PWD"), "=", 1))
				printf("%s\n", get_value(env, "PWD") + 1);
			else
				printf("%s\n", get_value(env, "PWD"));
		}
		else
		{
			g_data.exit = 1;
			printf("pwd not find in env\n");
		}
	}
	else
		printf("%s\n", pwd);
	ft_free(pwd);
	return (0);
}
