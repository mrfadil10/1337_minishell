/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 21:33:06 by stemsama          #+#    #+#             */
/*   Updated: 2022/10/31 02:09:00 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

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
		free(c[i]);
		i--;
	}
	free(c);
}

static char	**fct(const char *s, char c, int i, int k)
{
	int		start;
	char	**rslt;

	rslt = (char **)malloc((nbrwords(s, c) + 1) * sizeof(char *));
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
		rslt[k] = ft_substr(s, start, i - start);
		if (rslt[k] == NULL)
		{
			motsfree (rslt, k);
			return (NULL);
		}
	}
	rslt[k] = 0;
	return (rslt);
}

char	**ft_split(char const *s, char c)
{
	if (!s)
		return (NULL);
	return (fct (s, c, 0, -1));
}
