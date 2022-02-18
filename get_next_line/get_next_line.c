/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnukihiroki <ohnukihiroki@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 18:23:09 by hohnuki           #+#    #+#             */
/*   Updated: 2022/02/19 03:17:29 by ohnukihirok      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*store_to_save(char *save)
{
	char	*str;
	size_t	i;

	i = 0;
	while (save[i] != '\0' && save[i] != '\n')
		i++;
	if (save[i] == '\0')
	{
		free (save);
		return (NULL);
	}
	str = ft_substr_gnl(save, i + 1, ft_strlen_gnl(save));
	free(save);
	return (str);
}

static char	*trimming_save(char	*save)
{
	char	*str;
	size_t	i;

	if (save[0] == '\0')
		return (NULL);
	i = 0;
	while (save[i] != '\0' && save[i] != '\n')
		i++;
	str = ft_substr_gnl(save, 0, i + 1);
	return (str);
}

static char	*join_to_save(int fd, char *save)
{
	char	*buf;
	ssize_t	read_ret;

	if (BUFFER_SIZE == INT_MAX)
		buf = (char *)malloc (sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	else
		buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	read_ret = NOT_EOF_OR_ERROR;
	while (!ft_strchr_gnl(save, '\n') && read_ret != 0)
	{
		read_ret = read(fd, buf, BUFFER_SIZE);
		if (read_ret == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[read_ret] = '\0';
		save = ft_strjoin_gnl(save, buf);
	}
	free(buf);
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || INT_MAX < BUFFER_SIZE)
		return (NULL);
	save = join_to_save(fd, save);
	if (save == NULL)
		return (NULL);
	line = trimming_save(save);
	save = store_to_save(save);
	return (line);
}
