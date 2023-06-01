/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lnt_env_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:30:09 by mfadil            #+#    #+#             */
/*   Updated: 2023/06/01 18:53:56 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	arg_token_lnt(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
	{
		if (str[i] == '\\' && (str[i + 1] == '"' || str[i + 1] == '\\'))
			i++;
		i++;
	}
	return (i);
}

int	char_strlen(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}
