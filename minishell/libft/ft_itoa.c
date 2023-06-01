/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 16:41:13 by stemsama          #+#    #+#             */
/*   Updated: 2022/10/16 15:53:55 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size(long int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		i++;
		n = -n;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}	

char	*ft_itoa(int n)
{
	char		*p;
	int			s;
	long int	nb;

	nb = n;
	s = ft_size(nb);
	p = (char *)malloc(sizeof(char) * (s + 1));
	if (p == 0)
		return (NULL);
	p[s] = '\0';
	if (nb == 0)
		p[0] = '0';
	if (nb < 0)
	{
		p[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		p[s - 1] = (nb % 10) + 48;
		nb = nb / 10;
		s--;
	}
	return (p);
}
