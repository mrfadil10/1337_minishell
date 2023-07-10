/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:37:10 by mfadil            #+#    #+#             */
/*   Updated: 2023/07/10 22:50:48 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	herdoc_expander(t_data *node, char **env)
{
	char	*line;
	int		i;

	g_data.signal = 1;
	line = readline("> ");
	type_lstadd_back(line, 1);
	if (pipe(node->pipe) == -1)
		exit (1);
	while (line && g_data.heredoc == 1 && ft_strcmp(line, node->next->av[0]))
	{
		
	}
}