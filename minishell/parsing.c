/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:43:30 by stemsama          #+#    #+#             */
/*   Updated: 2023/07/06 23:18:23 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static int	parse_semicolon(t_data *parameter)
//{
//	if (!parameter->str || ft_memcmp(parameter->str, ";", 2))
//	{
//		if (parameter->str)
//			ft_putstr_fd("bash: syntax error near unexpected token `;'\n", 2);
//		free(parameter->str);
//		return (1);
//	}
//	return (0);
//}

//static int	parse_quotes(int i, char **str)
//{
//	i++;
//	while (*str[i] && (*str[i] != '\'' || *str[i] != '\"'))
//		i++;
//	if (!(*str)[i])
//	{
//		ft_putstr_fd("Quotes not closed\n", 2);
//		return (1);
//	}
//	return (0);
//}

//static int	check_env(t_data *parameter, char **str)
//{
//	int	i;
//	int	brace;

//	i = 0;
//	brace = 0;
//	while ((*str) && (*str)[i])
//	{
//		if (parse_quotes(&i, str) && (*str)[i] == '\'')
//			return (1);
//	}
//}

//void	free_matrice(char **matrice)
//{
//	int	i;

//	i = 0;
//	if (!matrice)
//		return ;
//	while (matrice[i])
//		free(matrice[i++]);
//	free(matrice);
//}

void	rep_sp(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\t' || str[i] == '\r')
			str[i] = ' ';
		i++;
	}
}

int	check_sep(char *sep, char s)
{
	int	i;

	i = -1;
	while (sep[++i])
		if (s == sep[i])
			return (1);
	return (0);
}

void	token_str(t_data *data, char **str, int *lnt)
{
	int		c;
	char	*line;

	line = *str;
	if (*(line - 1) == ' ')
		c = 1;
	else
		c = 0;
	while (*line && check_sep("\"'<>|", *line) == 0)
	{
		line++;
		(*lnt)++;
	}
	
}

t_data	*tokenize(char *line)
{
	int		i;
	t_data	*data;

	data = NULL;
	rep_sp(line);
	while (*line != '\0')
	{
		while (*line == ' ')
			line++;
		if (!(*line))
			break ;
		if (!check_sep("\"'<>|", *line))
			;
	}
}

void	parsing(t_data *parameter)
{
	int	i;

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
