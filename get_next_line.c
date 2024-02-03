/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbezerra <tbezerra@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:15:51 by tbezerra          #+#    #+#             */
/*   Updated: 2024/01/31 11:45:38 by tbezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*rest = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	rest = file_read(fd, rest);
	if (!rest)
		return (NULL);
	line = get_line(rest);
	rest = ft_next(rest);
	return (line);
}

/* #include <stdio.h>
#include <fcntl.h>

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