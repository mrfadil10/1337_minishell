/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 17:21:59 by stemsama          #+#    #+#             */
/*   Updated: 2022/10/31 02:18:46 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > (ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	dest = (char *)malloc(sizeof(char) * (len) + 1);
	if (dest == 0 || s == 0)
		return (0);
	if (start >= ft_strlen(s))
	{
		*dest = '\0';
		return (dest);
	}
	ft_strlcpy(dest, (s + start), len + 1);
	return (dest);
}
