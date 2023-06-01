/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 07:59:43 by stemsama          #+#    #+#             */
/*   Updated: 2022/10/16 15:54:11 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = -1;
	while (n > ++i)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return ((void *)(s + i));
	}
	return (0);
}
