/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:30:32 by mfadil            #+#    #+#             */
/*   Updated: 2023/06/07 12:13:35 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtins(t_data *parameter, int fd)
{
	char	cur[4097];
	char	*path;

	path = 0;
	if (!ft_memcmp(parameter->av[0], "echo", 5))
		execute_echo(parameter->av);
	else if (!ft_memcmp(parameter->av[0], "pwd", 4))
		execute_pwd(parameter->av);
	else if (!ft_memcmp(parameter->av[0], "cd", 3))
	{
		path = ft_strdup(parameter->av[1]);
		// implement cd
	}
}

int	check_builtins(t_data *parameter, int fd)
{
	parameter->ret = 0;
	if ()
}