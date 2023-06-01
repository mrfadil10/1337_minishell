/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 21:38:53 by stemsama          #+#    #+#             */
/*   Updated: 2023/05/06 16:07:25 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	// if (.. > LLONG_MAX LLONG_MIN)
	return (1);
}

int	execute_exit(char **argv)
{
	printf("exit\n");
	if (!argv[0])
		exit(0);
	if ((!ft_isnumber(argv[0])) || (ft_atoi(argv[0]) == 1))
		printf("minishell: exit: %s: numeric argument required\n", *argv);
	//num long long
	else if (argv[1])
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	exit(0);
}
