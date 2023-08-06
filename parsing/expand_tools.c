/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:37:10 by mfadil            #+#    #+#             */
/*   Updated: 2023/08/06 18:12:02 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_index(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && (str[i + 1] == '?'
				|| str[i + 1] == '_' || (ft_isalnum(str[i + 1]))))
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

	i = -1;
	tmp = ft_strjoin(str + 1, "=");
	lnt = ft_strlen(tmp);
	value = NULL;
	if (!ft_strcmp(str, "$?"))
		return (ft_itoa(g_data.exit));
	while (env[++i])
		if (!ft_strncmp(tmp, env[i], lnt))
			value = type_strdup(&env[i][lnt], 1);
	if (value == NULL)
		value = type_strdup("", 1);
	return (value);
}

char	*insert(char *str1, char *str2, int size, int index)
{
	int		i;
	int		j;
	int		lnt;
	char	*tmp;

	i = 0;
	j = size + index;
	tmp = str1;
	lnt = (ft_strlen(str1) - size) + ft_strlen(str2);
	str1 = back_alloc(sizeof(char) * (lnt + 1), 1);
	while (i < index)
	{
		str1[i] = tmp[i];
		i++;
	}
	while (*str2)
	{
		str1[i] = *str2++;
		i++;
	}
	while (tmp[j])
		str1[i++] = tmp[j++];
	str1[i] = '\0';
	return (str1);
}

char	*get_line(char *line, char **env, int idx)
{
	int		i;
	char	*str;
	char	*sub_ret;
	char	*tmp;

	i = 0;
	while (idx >= 0)
	{
		tmp = line;
		i = get_lnt(&line[idx]);
		sub_ret = type_substr(line, idx, 1, i);
		str = get_var_value(sub_ret, env);
		line = insert(line, str, i, idx);
		idx = get_index(line);
	}
	return (line);
}
