/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbones <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 16:25:14 by lbones            #+#    #+#             */
/*   Updated: 2021/01/19 05:20:39 by lbones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

size_t	ft_strlen1(char *a);
char	*ft_strchr1(const char *s, int c);
char	*ft_strdup1(const char *s1);
char	*ft_strjoin1(char const *s1, char const *s2);
int		get_next_line(int fd, char **line);
#endif
