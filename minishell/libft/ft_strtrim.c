/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 10:12:59 by stemsama          #+#    #+#             */
/*   Updated: 2022/10/30 19:10:13 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cheek_set(const char c_s1, const char *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c_s1 == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	get_first_p(const char *s1, const char *set)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && cheek_set(s1[i], set) == 1)
	{
		i++;
	}
	return (i);
}

static int	get_last_p(const char *s1, const char *set)
{
	int	j;

	j = ft_strlen(s1) - 1 ;
	while (j >= 0 && cheek_set(s1[j], set) == 1)
	{
		j--;
	}
	return (j);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*p;
	int		fin;
	int		fst;
	int		len;
	int		i;

	i = 0;
	if (s1 == 0 || set == 0)
		return (NULL);
	fst = get_first_p(s1, set);
	fin = get_last_p(s1, set);
	len = fin - fst + 1;
	if (fst == (int)ft_strlen(s1))
		return (ft_strdup(""));
	p = (char *)malloc(sizeof(char) * len + 1);
	if (!p)
		return (NULL);
	while (i < len)
	{
		p[i] = s1[fst];
		i += 1;
		fst += 1;
	}
	p[i] = '\0';
	return (p);
}
