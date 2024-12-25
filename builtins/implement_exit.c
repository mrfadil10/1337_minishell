/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 21:38:53 by stemsama          #+#    #+#             */
/*   Updated: 2023/08/13 15:58:40 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isnumber(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	if ((*str == '+' || *str == '-') && *(str + 1))
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	execute_exit(char **argv)
{
	printf("exit\n");
	if (argv[1])
		g_data.exit = ft_atoi(argv[1]);
	if (!argv[1])
		exit(g_data.exit);
	if ((!ft_isnumber(argv[1])) || ((ft_atoi2(argv[1]) == 1) && \
	(g_data.atoi_exit == 1)))
	{
		printf("minishell: exit: %s: numeric argument required\n", argv[1]);
		g_data.exit = 255;
	}
	else if (argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	exit(g_data.exit);
}
