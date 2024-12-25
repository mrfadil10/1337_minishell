/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdc_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 18:11:28 by mfadil            #+#    #+#             */
/*   Updated: 2023/08/13 17:23:31 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_int2(int sig)
{
	if (sig == SIGINT)
	{
		g_data.hrdc_sig_c = 1;
		ioctl(0, TIOCSTI, "\4");
		g_data.exit = 1;
	}
}

int	hrdc_norm1(t_data	*node, t_data *node2, int *fd1, char **env)
{
	t_data	*node_hrdc;

	node_hrdc = node2;
	while (node)
	{
		node->out = -2;
		node->in = -2;
		if (node->t_type == HRDC)
		{
			if (*fd1 != -2)
				close(*fd1);
			*fd1 = open_file(node, node->next->av[0], &g_data.name);
			if ((*fd1 == -1) || (*fd1 == -42))
				return (-2);
			node_hrdc = node;
			g_data.flag = 0;
			node->next->t_type = FILEE;
			if ((node_hrdc != node2) || (g_data.flag == 0))
				if (herdoc_expander(node_hrdc, env, *fd1, g_data.name) == 1)
					return (1);
		}
		node = node->next;
	}
	return (0);
}

int	hrdc(t_data	*node2, int *fd1, char **env)
{
	t_data	*node;
	t_data	*node_hrdc;
	int		c;

	g_data.name = NULL;
	g_data.flag = 1;
	node = node2;
	node_hrdc = node2;
	g_data.hrdc_sig_c = 0;
	c = hrdc_norm1(node, node2, fd1, env);
	if (c == 1)
		return (1);
	else if (c == -2)
		return (-2);
	return (0);
}

void	herdoc_expander_norm1(char *line, char **env, int fd1, char *limeter)
{
	int		i;

	while (line && ft_strcmp(line, limeter))
	{
		i = get_index(line);
		if (i >= 0)
			line = get_line(line, env, i);
		write(fd1, line, ft_strlen(line));
		write(fd1, "\n", 1);
		ft_free(line);
		line = ft_readline("heredoc> ");
	}
}

int	herdoc_expander(t_data *node, char **env, int fd1, char *name)
{
	char	*line;
	char	*limeter;

	(void) env;
	g_data.signal = 1;
	signal(SIGINT, sig_int2);
	if (!ft_strcmp("\"\"", node->next->av[0]))
		node->next->av[0] = type_strdup("");
	line = ft_readline("heredoc> ");
	limeter = passe_sep2(node->next->av[0], '"');
	limeter = passe_sep2(limeter, '\'');
	herdoc_expander_norm1(line, env, fd1, limeter);
	close(fd1);
	fd1 = open(name, O_RDONLY, 0777);
	unlink(name);
	if (fd1 == -1)
		return (1);
	if (g_data.hrdc_sig_c == 1)
		return (1);
	return (0);
}
