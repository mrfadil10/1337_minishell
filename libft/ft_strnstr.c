/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 09:29:15 by stemsama          #+#    #+#             */
/*   Updated: 2022/10/23 13:41:31 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (!s1 && len == 0)
		return (NULL);
	if (!*s2)
		return ((char *)s1);
	while (s1[i])
	{
		j = 0;
		while (s1[i] == s2[j] && s1[i] && i < len)
		{
			i++;
			j++;
		}
		if (!s2[j])
			return ((char *)s1 + (i - j));
		i = (i - j) + 1;
	}
	return (NULL);
}
