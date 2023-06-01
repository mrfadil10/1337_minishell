/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 23:47:53 by mfadil            #+#    #+#             */
/*   Updated: 2023/06/01 15:47:52 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_sp(char **str)
{
	while (**str == ' ' || (**str >= 9 && **str <= 13))
		*str++;
}

int	arg_len(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '=' || str[i] == '|' || str[i] == '<' || str[i] == '>')
	{
		i++;
		if (str[i] == '>' && str[i] == '>')
			i++;
	}
	else
	{
		while (str[i] && !(str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			&& str[i] != '=' && str[i] != '|' && str[i] != '<' && str[i] != '>')
		{
			if (str[i] == '"' || str[i] == '\'')
			{
				i++;
				i += arg_token_lnt(str + i, str[i - 1]);
				if (!str[i])
					return (i);
			}
			i++;
		}
		if (str[i] == '=')
			i++;
	}
	return (i);
}

int	arg_counter(char *str)
{
	int	nb;

	nb = 0;
	skip_sp(&str);
	while (*str)
	{
		skip_sp(&str);
		nb++;
		str += arg_len(str);
		skip_sp(&str);
	}
	return (nb);
}

void	set_arguments(int ac, char **av, char *str)
{
	int	lnt;
	int	i;

	i = 0;
	skip_sp(&str);
	while (i < ac)
	{
		skip_sp(&str);
		lnt = arg_len(str);
		av[i] = ft_strldup(str, lnt);
	}
}
