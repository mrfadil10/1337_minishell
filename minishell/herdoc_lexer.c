/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:37:10 by mfadil            #+#    #+#             */
/*   Updated: 2023/07/11 22:05:05 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_index(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && (str[i + 1] == '?' || str[i + 1] == '_'
				|| (ft_isalnum(str[i + 1]))))
			return (i);
		i++;
	}
	return (-1);
}

int	get_lnt(char *str)
{
	int	i;

	i = 0;
	str++;
	if (str[i] == '?')
		return (2);
	while (str[i] == '_' || ft_isalnum(str[i]))
		i++;
	return (i + 1);
}

char	*get_var_value(char *str, char **env)
{
	char	*tmp;
	char	*value;
	int		lnt;
	int		i;

	value = NULL;
	tmp = ft_strjoin(str + 1, "="); // missing type in strjoin
	lnt = ft_strlen(tmp);
	if (!ft_strcmp(str, "$$"))
		return (ft_itoa(getpid())); // missing type here
	if (!ft_strcmp(str, "$?"))
		return (ft_itoa(g_data.exit)); // same
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(str, env[i], lnt))
			value = ft_strdup(&env[i][lnt]); // khssni nzid whd parameter hna
	}
	if (!value)
		value = ft_strdup("");
	return (value);
}

char	*get_line(char *line, char **env, int idx)
{
	char	*tmp;
	char	*str;
	char	*sub_ret;
	int		i;

	i = 0;
	while (idx >= 0)
	{
		tmp = line;
		i = get_lnt(&line[idx]);
		sub_ret = type_substr(line, idx, 1, i);
		str = get_var_value(sub_ret, env);
	}
}

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
		i = get_index(line);
		if (i != -1)
			line = get_line()
	}
}