/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 10:20:10 by stemsama          #+#    #+#             */
/*   Updated: 2022/10/30 23:22:15 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t elt, size_t size)
{
	char	*pt;
	size_t	i;

	i = 0;
	if (elt != 0 && SIZE_MAX / elt < size)
		return (NULL);
	pt = malloc(elt * size);
	if (pt == NULL)
		return (NULL);
	while (i < elt * size)
	{
		pt[i] = 0;
		i++;
	}
	return (pt);
}
