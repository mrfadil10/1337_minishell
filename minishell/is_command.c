/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 20:17:24 by mfadil            #+#    #+#             */
/*   Updated: 2023/06/05 00:02:31 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirection(t_data *parameter, int fd, int i)
{
	char	c;
	int		read_ret;

	while (parameter->av[i])
	{
		if (!ft_memcmp(parameter->av[i], ">>", 3))
		{
			fd = open(parameter->av[i + 1], O_CREAT, O_RDWR, O_APPEND, 0777);
			read_ret = 0;
			while (read_ret = read(fd, &c, 1))
			{
				if (read_ret == -1)
				{
					write(2, "Couldn't read this file", 23);
					break ;
				}
			}
		}
		else if (!ft_memcmp(parameter->av[i], ">", 2))
			fd = open(parameter->av[i + 1], O_CREAT, O_TRUNC, O_RDWR, 0777);
		i++;
		if (parameter->av[i] && (!ft_memcmp(parameter->av[i], ">>", 3)
				|| !ft_memcmp(parameter->av[i], ">", 2)))
			close(fd);
	}
	return (fd);
}

static int	get_fd(t_data *parameter)
{
	int	fd;
	int	i;

	i = 0;
	fd = 1;
	while (parameter->av[i] && ft_memcmp(parameter->av[i], ">", 2)
		&& ft_memcmp(parameter->av[i], ">>", 2))
		i++;
	if (parameter->av[i] == NULL)
		return (1);
	else
		return (redirection(parameter, fd, i));
}

static int	copy_arguments(t_data *param)
{
	char	**args;
	int		i;
	int		j;

	
}

char	**is_command(char *str, t_data *parameter)
{
	int	fd;

	if (parameter->av[0] && *(parameter->av[0]))
	{
		fd = get_fd(parameter);

	}
}
