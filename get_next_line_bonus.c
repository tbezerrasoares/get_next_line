/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbezerra <tbezerra@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:48:58 by tbezerra          #+#    #+#             */
/*   Updated: 2024/01/31 12:20:08 by tbezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_next(char *rest)
{
	char	*line;
	int		i;
	int		j;

	i = check_char(rest, '\n');
	if (i < 0 || !rest[0])
	{
		free(rest);
		return (0);
	}
	line = malloc(ft_strlen(rest) - i);
	i++;
	j = -1;
	while (rest[i + (++j)] != 0)
		line[j] = rest[i + j];
	line[j] = 0;
	free(rest);
	return (line);
}

static char	*get_line(char *rest)
{
	char	*line;
	int		i;
	int		j;

	j = 0;
	if (!rest[0])
		return (0);
	i = check_char(rest, '\n');
	if (i == -1)
		i = ft_strlen(rest);
	line = malloc(i + 2);
	if (!line)
		return (0);
	while (i >= j)
	{
		line[j] = rest[j];
		j ++;
	}
	line[j] = 0;
	return (line);
}

static char	*file_read(int fd, char *rest)
{
	char	*line;
	int		size;

	if (!rest)
	{
		rest = malloc(1);
		rest[0] = 0;
	}
	size = 1;
	line = NULL;
	while (check_char(rest, '\n') < 0 && size > 0)
	{
		line = malloc(BUFFER_SIZE + 1);
		size = read(fd, line, BUFFER_SIZE);
		if (size <= 0)
			return (ft_erro(rest, line, size));
		line[size] = 0;
		rest = ft_strjoin(rest, line);
		free(line);
	}
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*rest[FOPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX)
		return (NULL);
	rest[fd] = file_read(fd, rest[fd]);
	if (!rest[fd])
		return (NULL);
	line = get_line(rest[fd]);
	rest[fd] = ft_next(rest[fd]);
	return (line);
}

/* 
# include <fcntl.h>

int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
	int		fd2;
	fd1 = open("read_error.txt", O_RDONLY);
	fd2 = open("test.txt", O_RDONLY);
	

	i = 1;
	line = get_next_line(fd1);
	while (line)
	{
		printf("line [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd1);
		i++;
	}
 	i = 1;
	line = get_next_line(fd2);
	while (line)
	{
		printf("line [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd2);
		i++;
	}
	close(fd1);
	close(fd2);
	return (0);
} */