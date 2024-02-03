/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbezerra <tbezerra@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:11:47 by tbezerra          #+#    #+#             */
/*   Updated: 2024/01/31 12:21:33 by tbezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_erro(char *rest, char *line, int size)
{
	free(line);
	line = 0;
	if (size == -1)
	{
		free(rest);
		rest = 0;
		return (0);
	}
	return (rest);
}

char	*ft_strjoin(char *rest, char *line)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = malloc(ft_strlen(rest) + ft_strlen(line) + 1);
	if (!tmp || !(rest) || !line)
		return (0);
	i = 0;
	j = 0;
	while ((rest)[i] != 0)
	{
		tmp[i] = (rest)[i];
		i++;
	}
	while (line[j] != 0)
	{
		tmp[i + j] = line[j];
		j++;
	}
	tmp[i + j] = 0;
	free(rest);
	return (tmp);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (*str != 0)
	{
		str ++;
		i++;
	}
	return (i);
}

int	check_char(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != 0)
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
