/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:56:55 by stemsama          #+#    #+#             */
/*   Updated: 2022/10/16 15:54:22 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*sc;
	unsigned char		*dt;

	if (!dest && !src)
		return (0);
	dt = (unsigned char *)dest;
	sc = (const unsigned char *)src;
	while (n-- > 0)
	{
		*dt++ = *sc++;
	}
	return (dest);
}
