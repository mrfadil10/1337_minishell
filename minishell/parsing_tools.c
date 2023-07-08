/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 19:59:54 by mfadil            #+#    #+#             */
/*   Updated: 2023/07/08 19:36:13 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

//char	**split_case(char *str, char c)
//{
//	char	**matrice;
//	int		i;

//	if (!str)
//		return (NULL);
//	i = str_numbers(str, c);
//	matrice = (char **)ft_calloc(sizeof(char *), i + 1);
//	if (!matrice)
//		return (NULL);
//	set_matrice(matrice, str, c, i);
//	return (matrice);
//}

void	put_back(t_data *data, char *str, int type, int lnt)
{
	t_data	*list;
	char	*s;

	if (str && (type == SIQUOTE || type == DOQUOTE || type == COMMND))
		s = type_substr(str - lnt, 0, 1, lnt);
	else
		s = NULL;
	
}
