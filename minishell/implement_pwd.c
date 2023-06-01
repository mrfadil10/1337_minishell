/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_pwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 23:13:48 by stemsama          #+#    #+#             */
/*   Updated: 2023/04/17 22:20:44 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_pwd(t_env **env)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		if (get_value(env, "PWD"))
			printf("%s\n", get_value(env, "PWD"));
		else
			printf("pwd not find in env\n");
	}
	else
		printf("%s\n", pwd);
}
