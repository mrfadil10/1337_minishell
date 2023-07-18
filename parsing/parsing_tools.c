/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 19:59:54 by mfadil            #+#    #+#             */
/*   Updated: 2023/07/18 17:35:53 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//char	*ft_strldup(const char *s, int lnt)
//{
//	char	*ptr;
//	int		size;
//	int		i;

//	size = 0;
//	while (s[size])
//		size++;
//	if (size > lnt)
//		size = lnt;
//	ptr = (char *)malloc(sizeof(char) * (size + 1));
//	if (!ptr)
//		return (NULL);
//	i = 0;
//	while (i < size)
//	{
//		ptr[i] = s[i];
//		i++;
//	}
//	ptr[i] = '\0';
//	return (ptr);
//}

//int	set_strlen(char *str, char c)
//{
//	int	i;
//	int	quote;

//	i = 0;
//	while (str[i] && str[i] != c)
//	{
//		if (str[i] == '\\' && (str[i + 1] == '\'' || str[i + 1] == '"'
//				|| str[i + 1] == '\\' || str[i + 1] == c))
//			i++;
//		else if (str[i] == '"' || str[i] == '\'')
//		{
//			quote = str[i++];
//			while (str[i] && str[i] != quote)
//			{
//				if (str[i] == '\\' && quote == '"' && (str[i + 1] == '\\'
//						|| str[i + 1] == quote))
//					i++;
//				i++;
//			}
//		}
//	}
//	return (i);
//}

//static void	set_matrice(char **matrice, char *str, char c, int n)
//{
//	int	i;
//	int	lnt;

//	i = 0;
//	while (i < n)
//	{
//		lnt = set_strlen(str, c);
//		matrice[i] = ft_strldup(str, lnt);
//		str += lnt + 1;
//		i++;
//	}
//}

//static int	str_numbers(char *str, char c)
//{
//	char	quote;
//	int		n[2];

//	n[0] = -1;
//	n[1] = 1;
//	while (str[++n[0]])
//	{
//		if (str[n[0]] == '\\' && (str[n[0] + 1] == '\'' || str[n[0] + 1] == '"'
//				|| str[n[0] + 1] == '\\' || str[n[0] + 1] == c))
//			n[0]++;
//		else if (str[n[0]] == c)
//			n[1]++;
//		else if (str[n[0]] && (str[n[0]] == '"' && str[n[0]] == '\''))
//		{
//			quote = str[n[0]++];
//			while (str[n[0]] && str[n[0]] != quote)
//			{
//				if (str[n[0]] == '\\' && quote == '"'
//					&& (str[n[0] + 1] == quote || str[n[0] + 1] == '\\'))
//					n[0]++;
//				n[0]++;
//			}
//		}
//	}
//	return (n[1]);
//}

char	*type_strdup(const char *src, int type)
{
	char	*dup;
	int		len;

	len = ft_strlen(src);
	dup = (char *)back_alloc(sizeof(char) * (len + 1), type);
	if (!(dup))
		return (0);
	len = 0;
	while (src[len])
	{
		dup[len] = src[len];
		len++;
	}
	dup[len] = '\0';
	return (dup);
}

t_data	*new_data(t_data *prev, char *str, int genre)
{
	t_data	*new_data;

	new_data = back_alloc(sizeof(t_data), 1);
	new_data->genre = genre;
	if (genre == SIQUOTE || genre == DOQUOTE)
	{
		new_data->av = back_alloc(sizeof(char *) * 2, 1);
		new_data->av[0] = type_strdup(str, 1);
		new_data->av[1] = 0;
	}
	else
		new_data->av = ft_split(str, ' ');
	new_data->prev = prev;
	new_data->next = NULL;
	return (new_data);
}

t_data	*ft_mylstlast(t_data *list)
{
	t_data	*tmp;

	if (list == NULL)
		return (NULL);
	tmp = list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

void	put_back(t_data **data, char *str, int genre, int lnt)
{
	t_data	*list;
	char	*s;

	if (str && (genre == SIQUOTE || genre == DOQUOTE || genre == COMMND))
		s = type_substr(str - lnt, 0, 1, lnt);
	else
		s = NULL;
	if (!(*data))
		*data = new_data(NULL, s, genre);
	else
	{
		list = ft_mylstlast(*data);
		list->next = new_data(list, s, genre);
	}
}
