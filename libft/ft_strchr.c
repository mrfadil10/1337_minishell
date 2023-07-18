/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:45:54 by stemsama          #+#    #+#             */
/*   Updated: 2022/10/16 15:55:09 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*b;
	int		i;
	int		len;

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
