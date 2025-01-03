/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:43:30 by stemsama          #+#    #+#             */
/*   Updated: 2023/08/12 21:39:30 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	str[0] = line;
	*lnt = 0;
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
		g_data.cheek = 1;
	}
	return (data);
}

int	lexer(t_data *data, char **env)
{
	t_data	*node;

	(void) env;
	node = data;
	if (ft_mylstlast(data)->t_type == HRDC || data->t_type == PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
			2);
		g_data.exit = 258;
		return (1);
	}
	while (node)
	{
		if (node->t_type != COMMND && node->t_type != SIQUOTE
			&& node->t_type != DOQUOTE)
			if (node->next
				&& error_pipe_hrdc_add(node->t_type, node->next->t_type))
				return (1);
		if (node->t_type == SIQUOTE || node->t_type == DOQUOTE)
			if (is_closed(node->av[0], node->t_type))
				return (1);
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
		g_data.exit = 258;
		return (NULL);
	}
	data = normalize(data);
	return (data);
}
	// protection dl env
	// skip space they are in the first string fcl echo
	// env | grep $HOME
	// expand differen in double quote
	// check quotes is pair
	// bash-3.2$ export test="file1 file2"
	// bash-3.2$ >hey >$test
	// bash: $test: ambiguous redirect