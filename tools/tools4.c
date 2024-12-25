/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 10:42:15 by stemsama          #+#    #+#             */
/*   Updated: 2023/08/13 16:29:55 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_export_norm_1(char **argv, t_env *cur)
{
	if (argv[1] == NULL)
	{
		while (cur)
		{
			if (cur->tag == 0)
			{
				printf("declare -x %s", get_name(cur->n_v));
				if (cur->value)
					printf("=\"%s\"\n", get_value1(cur->n_v) + 1);
				else
					printf("\n");
			}
			cur = cur->next;
		}
	}
}

int	ft_ispath(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi2(char *str)
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

int	ft_atoi_trois2(void)
{
	g_data.atoi_exit = 1;
	return (1);
}

int	ft_lstsize2(t_data *lst)
{
	int		a;

	a = 0;
	if (!lst)
		return (0);
	while (lst != 0)
	{
		lst = lst->next;
		a++;
	}
	return ((a + 1) / 2);
}
