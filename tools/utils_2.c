/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 20:36:27 by mfadil            #+#    #+#             */
/*   Updated: 2023/08/12 00:39:55 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**tab_fixed(char **str)
{
	int		i;
	int		j;
	char	**newtab;
	int		lnt;

	i = 0;
	lnt = ft_tablen(str);
	while (str[i])
	{
		if (str[i++][0] == '\0')
			lnt--;
	}
	i = 0;
	j = 0;
	newtab = ft_malloc(sizeof(char *) * (lnt + 1));
	while (str[i])
	{
		if (str[i][0])
			newtab[j++] = type_strdup(str[i]);
		i++;
	}
	newtab[j] = NULL;
	return (newtab);
}

char	*ft_mystrjoin(char *s1, char *s2)
{
	char	*p;
	int		size1;
	int		size2;
	int		i;
	int		j;

	if (s1 == NULL)
		return (s2);
	if (s2 == NULL)
		return (s1);
	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	p = (char *)ft_malloc(((size1 + size2) + 1) * sizeof(char));
	if (p == 0)
		return (NULL);
	i = 0;
	j = -1;
	while (s1[i] != '\0')
		p[++j] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		p[++j] = s2[i++];
	p[++j] = '\0';
	return (p);
}

char	*delete_one(char *str, int idx, int c)
{
	char	*new;
	int		i;
	int		j;

	new = ft_malloc(sizeof(char) * ft_strlen(str) - 1);
	if (!new)
		exit(g_data.exit);
	i = 0;
	j = 0;
	while (str[i])
	{
		while (i == c || i == idx)
			i++;
		if (str[i] == '\0')
			break ;
		new[j++] = str[i++];
	}
	new[j] = '\0';
	return (new);
}

void	handle_quotes(t_data *data)
{
	int		i;
	int		j;

	i = -1;
	while (data->av[++i])
	{
		j = 0;
		while (data->av[i][j])
		{
			if (data->av[i][j] == '\'' || data->av[i][j] == '"')
			{
				if (part_of_delete_quote(data, i, &j))
					break ;
			}
			else
				j++;
		}
	}
}
