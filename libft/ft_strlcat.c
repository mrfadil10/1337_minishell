/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:21:55 by stemsama          #+#    #+#             */
/*   Updated: 2022/10/31 01:27:50 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = ft_strlen(src);
	k = 0;
	if (dstsize == 0)
		return (i);
	j = ft_strlen(dst);
	if (dstsize <= j)
		return (i + dstsize);
	while ((j + k < dstsize - 1) && src[k])
	{
		*(dst + (j + k)) = *(src + k);
		k++;
	}
	*(dst + (j + k)) = '\0';
	return (j + i);
}
