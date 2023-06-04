/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:43:30 by stemsama          #+#    #+#             */
/*   Updated: 2023/06/03 16:25:42 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_semicolon(t_data *parameter)
{
	if (!parameter->str || ft_memcmp(parameter->str, ";", 2))
	{
		if (parameter->str)
			ft_putstr_fd("bash: syntax error near unexpected token `;'\n", 2);
		free(parameter->str);
		return (1);
	}
	return (0);
}

static int	parse_quotes(int i, char **str)
{
	i++;
	while (*str[i] && (*str[i] != '\'' || *str[i] != '\"'))
		i++;
	if (!(*str)[i])
	{
		ft_putstr_fd("Quotes not closed\n", 2);
		return (1);
	}
	return (0);
}

void	free_matrice(char **matrice)
{
	int	i;

	i = 0;
	if (!matrice)
		return ;
	while (matrice[i])
		free(matrice[i++]);
	free(matrice);
}

void	parsing(t_data *parameter)
{
	int	i;

	i = 0;
	if (parse_semicolon(parameter))
		return ;
	parameter->commands = split_case(parameter->str, ';');
	while (parameter->commands[i])
	{
		parameter->ac = arg_counter(parameter->commands[i]);
		parameter->av = (char **)ft_calloc(sizeof(char *), parameter->ac + 1);
		set_arguments(parameter->ac, parameter->av, parameter->commands[i]);
		
	}
	free_matrice(parameter->commands);
	printf("--> parsing <--\n");
}
