/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:00:46 by mfadil            #+#    #+#             */
/*   Updated: 2023/06/06 19:08:58 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_char(char **str, int i)
{
	char	*buf1;
	char	*buf2;

	buf1 = ft_strldup(*str, i);
	buf2 = ft_strdup(*str + i + 1);
	free(*str);
	*str = ft_strjoin(buf1, buf2);
	free(buf1);
	free(buf2);
}

// *i
void	remove_bkslash(char **str, int *i)
{
	while ((*str)[*i])
	{
		if ((*str)[*i] == '\\'
		&& ((*str)[*i + 1] == '\\' || (*str)[*i + 1] == '"'))
			remove_char(str, *i);
		else if ((*str)[*i] == '"')
			break ;
		(*i)++;
	}
}

void	remove_token(char **argv)
{
	int	i;

	i = 0;
	while ((*argv)[i])
	{
		if ((*argv)[i] == '\'')
		{
			remove_char(argv, i);
			i += char_strlen(*argv + i, '\'');
			remove_char(argv, i);
		}
		else if ((*argv)[i] == '"')
		{
			remove_char(argv, i);
			remove_bkslash(argv, &i);
			remove_char(argv, i);
		}
		else if (((*argv)[i] == '\\')
		&& ((*argv)[i + 1] == '\\' || (*argv)[i + 1] == '"'
			|| (*argv)[i + 1] == '\''))
			remove_char(argv, i++);
		else
			i++;
	}
}
