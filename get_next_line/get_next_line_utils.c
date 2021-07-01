/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbones <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 16:24:54 by lbones            #+#    #+#             */
/*   Updated: 2021/04/30 23:12:53 by lbones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen1(char *a)
{
	size_t	i;

	i = 0;
	while (a[i])
		i++;
	return (i);
}

char	*ft_strchr1(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
		{
			return ((char *)s);
		}
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (0);
}

char	*ft_strdup1(const char *s1)
{
	size_t	i;
	char	*s2;
	size_t	i1;

	i1 = 0;
	i = ft_strlen1((char *)s1);
	s2 = (char *)malloc(i + 1);
	if (!s2)
		return (NULL);
	while (i >= i1)
	{
		s2[i1] = s1[i1];
		i1++;
	}
	return (s2);
}

char	*ft_strjoin1(char const *s1, char const *s2)
{
	char	*s;
	size_t	len1;
	size_t	i;
	char	*tmp;

	tmp = (char *)s1;
	i = -1;
	if (!s1)
		return (ft_strdup1(s2));
	if (!s2)
		return (ft_strdup1(s1));
	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen1((char *)s1);
	s = malloc(sizeof(char) * (len1 + (ft_strlen1((char *)s2)) + 1));
	if (!(s))
		return (NULL);
	while (++i < len1)
		s[i] = s1[i];
	i = -1;
	while (++i < ft_strlen1((char *)s2))
		s[len1 + i] = s2[i];
	s[len1 + i] = '\0';
	free(tmp);
	return (s);
}
