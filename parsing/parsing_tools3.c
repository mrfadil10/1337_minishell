/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 19:15:16 by mfadil            #+#    #+#             */
/*   Updated: 2023/08/06 20:07:39 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	rep_sp(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '\t' || str[i] == '\r')
			str[i] = ' ';
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
