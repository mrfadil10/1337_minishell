/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:43:30 by stemsama          #+#    #+#             */
/*   Updated: 2023/07/18 21:36:10 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	if (*(line - 1) == 32)
		c = 1;
	else
		c = 0;
	while (*line && !check_sep("\"'<>|", *line))
	{
		(*lnt)++;
		line++;
	}
	put_back(data, line, COMMND, *lnt);
	ft_mylstlast(*data)->sp = c;
	*str = line;
	*lnt = 0;
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
	(*lnt)++;
	line++;
	while (*line != i && *(line++))
		(*lnt)++;
	line++;
	(*lnt)++;
	put_back(data, line, type, *lnt);
	ft_mylstlast(*data)->sp = j;
	*lnt = 0;
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
		i = 0;
		while (*line == ' ')
			line++;
		if (!(*line))
			break ;
		if (!check_sep("\"'<>|", *line))
			token_str(&data, &line, &i);
		else if (*line == '\'' || *line == '"')
			token_quotes(&data, &line, &i);
		else if (*line == '<' || *line == '>')
			token_redirect(&data, &line, &i);
		else if (*(line++) == '|')
			put_back(&data, NULL, PIPE, i);
	}
	return (data);
}

	//int	i;
	//int	j;
	//int	k;
	//int	l;

	//i = 0;
	//j = 0;
	//k = 0;
	//l = 0;

	//while (line[i])
	//{
	//	if (line[i] == '"')
	//	{
	//		l = 1;
	//		j++;
	//	}
	//	else if (line[i] == '\'' && l == 0)
	//		k++;
	//	i++;
	//}
	//if (k % 2 != 0 || j % 2 != 0)
	//{
	//	ft_putstr_fd("minishell: Syntax Error: quote not closed\n", 1);
	//	return (1);
	//}
	//return (0);

int	is_closed(char *str, int type)
{
	int		c;
	int		i;

	//printf("%s\n", str);

	i = 0;
	if (type == DOQUOTE)
		c = '"';
	else
		c = '\'';
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == '\0' || ft_strlen(str) == 1)
	{
		ft_putstr_fd("minishell: quote not closed\n", 1);
		return (1);
	}
	return (0);
}

//int	parse_quotes(int i, char **str)
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

int	error_sup_inf(int genre, int next)
{
	if (next == SUPERIOR && genre != PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 1);
		return (1);
	}
	if (next == INFERIOR && genre != PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", 1);
		return (1);
	}
	return (0);
}

int	error_pipe_hrdc_add(int	genre, int next)
{
	if (genre == PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 1);
		return (1);
	}
	if (next == HRDC && genre != PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `<<'\n", 1);
		return (1);
	}
	if (next == ADD && genre != PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `>>'\n", 1);
		return (1);
	}
	if (error_sup_inf(genre, next))
		return (1);
	return (0);
}

int	lexer(t_data *data, char **env)
{
	t_data	*node;

	node = data;
	if (data->genre == HRDC || ft_mylstlast(data)->genre == PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
			1);
		return (1);
	}
	while (node)
	{
		//	printf("1------>%s\n", node->av[0]);
		//	printf("2------>%s\n", node->av[1]);
		//	printf("3------>%s\n", node->next->av[0]);
		//	printf("4------>%s\n", node->next->av[1]);
		//printf("start av[0] == %s\n", node->av[0]);
		//printf("start type == %d\n", node->genre);
		if (node->genre != COMMND && node->genre != SIQUOTE
			&& node->genre != DOQUOTE)
		{
			if (node->next
				&& error_pipe_hrdc_add(node->genre, node->next->genre))
				return (1);
		}
		if (node->genre == SIQUOTE || node->genre == DOQUOTE)
		{
			if (is_closed(node->av[0], node->genre))
				return (1);
		}
		if (node->genre == HRDC)
			herdoc_expander(node, env);
		//printf("end av[0] == %s\n", node->av[0]);
		//printf("end type == %d\n", node->genre);
		node = node->next;
	}
	return (0);
}

t_data	*parsing(char *line, char **env)
{
	t_data	*data;
	t_data	*tmp;

	data = tokenize(line);
	if (!data)
		return (NULL);
	if (lexer(data, env))
		return (NULL);
	tmp = ft_mylstlast(data);
	if (tmp->genre == SUPERIOR || tmp->genre == INFERIOR || tmp->genre == ADD
		|| tmp->genre == HRDC || tmp->genre == PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
			1);
		return (NULL);
	}
	return (data);
}
