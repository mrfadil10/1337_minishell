/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 21:35:37 by stemsama          #+#    #+#             */
/*   Updated: 2023/08/13 16:52:39 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*p;
	int		size1;
	int		size2;
	int		i;
	int		j;

	if (s1 == NULL)
		return (s2);
	if (s2 == NULL)
		return (s1);
	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	p = (char *)malloc(((size1 + size2) + 1) * sizeof(char));
	if (p == 0)
		return (NULL);
	i = 0;
	j = -1;
	while (s1[i] != '\0')
		p[++j] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		p[++j] = s2[i++];
	p[++j] = '\0';
	return (p);
}
