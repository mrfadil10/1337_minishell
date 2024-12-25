/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 23:55:52 by mfadil            #+#    #+#             */
/*   Updated: 2023/08/13 19:22:54 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_closed(char *str, int type)
{
	int		c;
	int		i;

	i = 0;
	if (type == DOQUOTE)
		c = '"';
	else
		c = '\'';
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == '\0' || ft_strlen(str) == 1)
	{
		ft_putstr_fd("minishell: quote not closed\n", 1);
		g_data.exit = 258;
		return (1);
	}
	return (0);
}

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

char	*ft_myitoa(int n)
{
	char		*p;
	int			s;
	long int	nb;

	nb = n;
	s = ft_size(nb);
	p = (char *)ft_malloc(sizeof(char) * (s + 1));
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
