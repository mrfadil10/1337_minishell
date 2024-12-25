/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:45:54 by stemsama          #+#    #+#             */
/*   Updated: 2023/08/10 18:19:51 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*b;
	int		i;
	int		len;

	if (!s)
		return (NULL);
	i = 0;
	b = (char *)s;
	len = ft_strlen(s);
	while (i <= len)
	{
		if (*b == (char)c)
			return (b);
		i++;
		b++;
	}
	return (NULL);
}
