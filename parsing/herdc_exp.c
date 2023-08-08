/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdc_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 18:11:28 by mfadil            #+#    #+#             */
/*   Updated: 2023/08/08 15:40:10 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	herdoc_expander(t_data *node, char **env)
{
	int		i;
	char	*line;

	g_data.signal = 1;
	g_data.heredoc = 1;
	if (pipe(node->pipe) == -1)
		exit (1);
	line = readline("heredoc> ");
	type_lstadd_back(line, 1);
	while (line && ft_strcmp(line, node->next->av[0])
		&& g_data.heredoc == 1)
	{
		i = get_index(line);
		if (i >= 0)
			line = get_line(line, env, i);
		write(node->pipe[1], line, ft_strlen(line));
		write(node->pipe[1], "\n", 1);
		line = readline("heredoc> ");
		type_lstadd_back(line, 1);
	}
	g_data.heredoc = 0;
	close(node->pipe[1]);
}
