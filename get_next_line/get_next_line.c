/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbones <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 22:21:39 by lbones            #+#    #+#             */
/*   Updated: 2021/04/30 23:09:58 by lbones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_check(char **rem1, char **line)
{
	char	*c;
	char	*tmp;

	c = ft_strchr1(*rem1, '\n');
	if (c)
	{
		tmp = *rem1;
		*c = '\0';
		*line = ft_strjoin1(*line, *rem1);
		*rem1 = ft_strdup1(++c);
		free(tmp);
		return (1);
	}
	else
	{
		*line = ft_strjoin1(*line, *rem1);
		return (0);
	}
}

int	ft_return(int len, char **line, char *buf)
{
	free(buf);
	buf = NULL;
	if (len < 0)
	{
		*line = NULL;
		return (-1);
	}
	if (!(*line))
		*line = ft_strdup1("");
	return (0);
}

int	ft_reminder(char **buf, char **line)
{
	if (*buf)
	{
		if (ft_check(buf, line))
			return (1);
		free(*buf);
		*buf = NULL;
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*buf;
	int			len;

	if (fd < 0 || BUFFER_SIZE < 1 || !line)
		return (-1);
	*line = NULL;
	if (ft_reminder(&buf, line))
		return (1);
	if (!buf)
	{
		free(buf);
		buf = malloc(BUFFER_SIZE + 1);
		if (!(buf))
			return (-1);
	}
	len = read(fd, buf, BUFFER_SIZE);
	while (len > 0)
	{
		buf[len] = '\0';
		if (ft_check(&buf, line))
			return (1);
		len = read(fd, buf, BUFFER_SIZE);
	}
	return (ft_return(len, line, buf));
}
