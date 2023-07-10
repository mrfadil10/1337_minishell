/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:43:30 by stemsama          #+#    #+#             */
/*   Updated: 2023/07/10 15:33:29 by mfadil           ###   ########.fr       */
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

void	token_str(t_data **data, char **str, int *lnt)
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
	put_back(data, line, COMMND, *lnt);
	*str = line;
	*lnt = 0;
	ft_mylstlast(*data)->sp = c;
}

void	partof_token_quotes(t_data **data, char *line, int *lnt, int i)
{
	*lnt++;
	line++;
	while (*line && *line != i)
	{
		line++;
		*lnt++;
	}
	*lnt++;
	line++;
}

void	token_quotes(t_data **data, char **str, int *lnt)
{
	int		i;
	int		j;
	int		type;
	char	*line;

	line = *str;
	i = *line;
	if (*(line - 1) == ' ')
		j = 1;
	else
		j = 0;
	if (i == '\"')
		type = DOQUOTE;
	else
		type = SIQUOTE;
	partof_token_quotes(data, line, lnt, i);
	put_back(data, line, type, lnt);
	*lnt = 0;
	ft_mylstlast(*data)->sp = j;
	*str = line;
}

void	token_redirect(t_data **data, char **str, int *lnt)
{
	int		i;
	char	*line;

	i = *str[0];
	*lnt = 1;
	line = ++(*str);
	if (*line == i)
	{
		*lnt = 2;
		line++;
	}
	if (i == '>')
	{
		if (*lnt == 1)
			put_back(data, NULL, SUPERIOR, *lnt);
		else if (*lnt == 2)
			put_back(data, NULL, ADD, *lnt);
	}
	else
	{
		if (*lnt == 1)
			put_back(data, NULL, INFERIOR, *lnt);
		else if (*lnt == 2)
			put_back(data, NULL, HRDC, *lnt);
	}
	*lnt = 0;
	*str = line;
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
			token_str(&data, &line, &i);
		else if (*line == '|')
			put_back(&data, NULL, PIPE, i);
		else if (*line == '<' || *line == '>')
			token_redirect(&data, &line, &i);
		else if (*line == '\'' || *line == '\"')
			token_quotes(&data, &line, &i);
		*line++;
	}
	return (data);
}
	//if (parse_semicolon(paramete))
	//	return ;
	//parameter->commands = split_case(parameter->str, ';');
	//while (parameter->commands[i])
	//{
	//	parameter->ac = arg_counter(parameter->commands[i]);
	//	parameter->av = (char **)ft_calloc(sizeof(char *), parameter->ac + 1);
	//	set_arguments(parameter->ac, parameter->av, parameter->commands[i]);
	//}
	//free_matrice(parameter->commands);

int	is_closed(char *str, int type)
{
	char	c;
	int		i;

	i = 1;
	if (type == DOQUOTE)
		c = '"';
	else
		c = '\'';
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == '\0' || ft_strlen(str) == 1)
	{
		ft_putstr_fd("minishell: quote not closed", 1);
		return (1);
	}
	return (0);
}

int	lexer(t_data *data, char **env)
{
	t_data	*node;

	node = data;
	if (data->genre == HRDC || ft_mylstlast(data)->genre == PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token \n", 1);
		return (1);
	}
	while (node)
	{
		if (node->genre == SIQUOTE || node->genre == DOQUOTE
			|| node->genre == HRDC)
		{
			if (node->genre == HRDC)
				
			if (is_closed(node->av[0], node))
				return (1);
		}
	}
}
t_data	parsing(char *line, char *env)
{
	t_data	*data;

	data = tokenize(line);
	if (!data)
		return (NULL);
	printf("--> parsing <--\n");
}
