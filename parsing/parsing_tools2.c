/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 18:59:53 by mfadil            #+#    #+#             */
/*   Updated: 2023/08/13 19:22:47 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error_sup_inf(int t_type, int next)
{
	if (next == SUPERIOR && t_type != PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
		g_data.exit = 258;
		return (1);
	}
	if (next == INFERIOR && t_type != PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", 2);
		g_data.exit = 258;
		return (1);
	}
	return (0);
}

int	error_pipe_hrdc_add(int t_type, int next)
{
	if (next == PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		g_data.exit = 258;
		return (1);
	}
	if (next == HRDC && t_type != PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `<<'\n", 2);
		g_data.exit = 258;
		return (1);
	}
	if (next == ADD && t_type != PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `>>'\n", 2);
		g_data.exit = 258;
		return (1);
	}
	if (error_sup_inf(t_type, next))
		return (1);
	return (0);
}

char	*init_red(char **str, int *lnt, int *i)
{
	*i = *str[0];
	*lnt = 1;
	return (++(*str));
}

void	token_redirect(t_data **data, char **str, int *lnt)
{
	int		i;
	char	*line;

	line = init_red(str, lnt, &i);
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
