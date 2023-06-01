/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:12:41 by stemsama          #+#    #+#             */
/*   Updated: 2023/05/25 23:38:05 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pars_echo(char **argv, int *is_n, int *i)
{
	int	k;
	int	j;

	j = 0;
	k = 0;
	while (argv[*i])
	{
		j = 0;
		if (argv[*i][j++] == '-')
		{
			while (argv[*i][j] && argv[*i][j] == 'n')
				j++;
			if (!argv[*i][j] && argv[*i][--j] == 'n')
				k = 1;
			if (k)
			{
				*is_n = 0;
				*i = *i + 1;
			}
			else
				break ;
		}
		else
			break ;
	}
}

int	execute_echo(char **argv)//list des commandes
{
	int	i;
	int	j;
	int	is_n;
	int	*i2;

	i = 0;
	i2 = &i;
	is_n = 1;
	if (argv)
		pars_echo(argv, &is_n, i2);
	else
		return (printf("\n"), 1);
	j = i;
	while (argv[i])
	{
		if (i != j)
			printf(" ");
		printf("%s", argv[i++]);
	}
	if (is_n)
		printf("\n");
	return (1);
}
