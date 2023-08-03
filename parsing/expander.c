/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:42:27 by mfadil            #+#    #+#             */
/*   Updated: 2023/08/02 22:32:08 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_key(char *str)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] == '"' && nb == 0)
			nb++;
		if (str[i] == '\'' && (nb % 2) == 0)
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
		}
		if (str[i] == '\0')
			break ;
		if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '$'
				|| str[i + 1] == '_' || str[i + 1] == '?'
				|| (str[i + 1] == '\'' && (nb % 2) == 0) || str[i + 1] == '"'))
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

int	get_size(char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	if (*(str + 1) == '$' || *(str + 1) == '?')
		return (2);
	if (*(str + 1) == '\'' || *(str + 1) == '"')
	{
		c = *(str + 1);
		while (str[i] != c)
			i++;
	}
	else
	{
		i = 0;
		while (str[++i])
			if (!ft_isalnum(str[i]) && str[i] != '_')
				break ;
	}
	return (i);
}

void	part_of_expand(t_data *data, char **env, int c)
{
	char	*str;
	char	*tmp;
	int		i;
	int		size;

	i = check_key(data->av[c]);
	while (i >= 0)
	{
		size = get_size(&data->av[c][i]);
		if (data->av[c][i + 1] != '\'' && data->av[c][i + 1] != '\"')
		{
			tmp = type_substr(data->av[c], i, 1, size);
			str = get_var_value(tmp, env);
		}
		else
		{
			tmp = type_substr(data->av[c], i + 1, 1, size - 1);
			str = tmp;
		}
		data->av[c] = insert(data->av[c], str, size, i);
		i = check_key(data->av[c]);
	}
}

void	expand(t_data *data, char **env)
{
	t_data	*tmp;
	int		i;

	i = 0;
	tmp = data;
	if (tmp->t_type != COMMND && tmp->t_type != SIQUOTE
		&& tmp->t_type != DOQUOTE)
		return ;
	while (tmp->av[i])
	{
		part_of_expand(tmp, env, i);
		i++;
	}
	tmp->av = tab_fixed(tmp->av);
	tmp->commands = tmp->av[0];
}

//int main(int ac, char **av)
//{
//	char	*line2 = av[1];

//	while (ft_strchr(line2, '$'))
//	{
//		line2 = expand(line2);
//	}
//}
