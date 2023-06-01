/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 10:01:01 by stemsama          #+#    #+#             */
/*   Updated: 2023/04/29 09:13:05 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_atoi(char *str)
{
	long long	res;
	long long	cas;
	int			sin;

	res = 0;
	sin = 1;
	if (ft_strcmp(str, "-2147483648") == 0)
		return (-2147483648);
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sin = -1;
		str++;
	}
	while (*str && *str <= '9' && *str >= '0')
	{
		cas = res;
		res = res * 10 + *str++ - 48;
		if (cas != res / 10)
			return (ft_atoi_trois());
	}
	return (res * sin);
}

int	ft_atoi_trois(void)
{
	return (1);
}
