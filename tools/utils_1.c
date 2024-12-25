/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 11:23:19 by mfadil            #+#    #+#             */
/*   Updated: 2023/08/13 17:23:42 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*type_substr(const char *str, unsigned int start, size_t lnt)
{
	char			*new_str;
	unsigned long	c;

	if (!str)
		return (NULL);
	if (ft_strlen(str) < start)
	{
		new_str = ft_malloc(1);
		if (!new_str)
			return (NULL);
		new_str[0] = '\0';
		return (new_str);
	}
	if (ft_strlen(str) < lnt)
		lnt = ft_strlen(str);
	new_str = (char *)ft_malloc(sizeof(char) * (lnt + 1));
	c = 0;
	while (start < ft_strlen(str) && c < lnt)
	{
		new_str[c] = str[start];
		start++;
		c++;
	}
	new_str[c] = '\0';
	return (new_str);
}

static int	nbrwords(const char *str, char c)
{
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (str[i])
	{
		while (str[i] && c == str[i])
			i++;
		if (str[i])
			k++;
		while (str[i] && c != str[i])
			i++;
	}
	return (k);
}

static void	motsfree(char **c, int i)
{
	while (i >= 0)
	{
		ft_free(c[i]);
		i--;
	}
	ft_free(c);
}

static char	**fct(const char *s, char c, int i, int k)
{
	int		start;
	char	**rslt;

	rslt = (char **)ft_malloc((nbrwords(s, c) + 1) * sizeof(char *));
	if (!rslt)
		return (0);
	while (++k < nbrwords(s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		rslt[k] = type_substr(s, start, i - start);
		if (rslt[k] == NULL)
		{
			motsfree (rslt, k);
			return (NULL);
		}
	}
	rslt[k] = 0;
	return (rslt);
}

char	**ft_mysplit(char const *s, char c)
{
	if (!s)
		return (NULL);
	return (fct (s, c, 0, -1));
}
