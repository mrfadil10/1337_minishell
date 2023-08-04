/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:43:30 by stemsama          #+#    #+#             */
/*   Updated: 2023/08/04 16:11:18 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	is_closed(char *str, int type)
{
	int		c;
	int		i;

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

int	error_sup_inf(int t_type, int next)
{
	if (next == SUPERIOR && t_type != PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 1);
		return (1);
	}
	if (next == INFERIOR && t_type != PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", 1);
		return (1);
	}
	return (0);
}

int	error_pipe_hrdc_add(int	t_type, int next)
{
	if (next == PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (1);
	}
	if (next == HRDC && t_type != PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `<<'\n", 2);
		return (1);
	}
	if (next == ADD && t_type != PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `>>'\n", 2);
		return (1);
	}
	if (error_sup_inf(t_type, next))
		return (1);
	return (0);
}

int	lexer(t_data *data, char **env)
{
	t_data	*node;

	node = data;
	// switch
	if (data->t_type == PIPE || ft_mylstlast(data)->t_type == HRDC)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
			2);
		return (1);
	}
	while (node)
	{
		//printf("0--%s\n", node->av[0]);
		//printf("1--%s\n", node->av[1]);
		//printf("2--%s\n", node->av[2]);
		//printf("token type: %d\n", node->t_type);
		if (node->t_type != COMMND && node->t_type != SIQUOTE
			&& node->t_type != DOQUOTE)
		{
			if (node->next
				&& error_pipe_hrdc_add(node->t_type, node->next->t_type))
				return (1);
		}
		if (node->t_type == SIQUOTE || node->t_type == DOQUOTE)
		{
			if (is_closed(node->av[0], node->t_type))
				return (1);
		}
		if (node->t_type == HRDC)
			herdoc_expander(node, env);
		node = node->next;
	}
	return (0);
}

t_data	*parsing(char *line, char **env)
{
	t_data	*data;
	t_data	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	data = tokenize(line);
	if (!data)
		return (NULL);
	if (lexer(data, env))
		return (NULL);
	tmp = ft_mylstlast(data);
	if (tmp->t_type == SUPERIOR || tmp->t_type == INFERIOR || tmp->t_type == ADD
		|| tmp->t_type == HRDC || tmp->t_type == PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
			1);
		return (NULL);
	}
	data = normalize(data);
	return (data);
}
	//tmp = data;
	//expand(data, env);

	//-------------------------------------------------

	//while (data->av[i])
	//{
	//	j = 0;
	//	while (data->av[i][j])
	//	{
	//		if (data->av[i][j] == '\'' || data->av[i][j] == '"')
	//		{
	//			if (part_of_delete_quote(data, i, &j))
	//				break ;
	//		}
	//		else
	//			j++;
	//	}
	//	i++;
	//}
	//data->commands = data->av[0];

	//-------------------------------------------------

	//int	i;
	//tmp = data;
	//while (tmp)
	//{
	//	i = 0;
	//	while (tmp->av && tmp->av[i])
	//	{
	//		printf("enter\n");
	//		tmp->av[i] = passe_sep2(tmp->av[i], '\'');
	//		printf("#######------exit-----#######\n");
	//		tmp->av[i] = passe_sep2(tmp->av[i], '"');
	//		i++;
	//	}
	//	tmp = tmp->next;
	//}
	// cat fiha mochkil f control c
	// unset kat segfaulti mlli
	// khssni n7ayd handle pid hit get_pid() is a forbidden function
	// env makit updatach
	// tabulation makhddamach
	// $HOME == is directory
	// protection dl env
	// skip space they are in the first string fcl echo