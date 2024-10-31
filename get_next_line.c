/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:45:55 by yenyilma          #+#    #+#             */
/*   Updated: 2024/10/31 05:15:07 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_read_file(char *garbage, int fd)
{
	int		i;
	char	*temp;	

	i = 0;
	temp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (NULL);
	while (!ft_strchr(garbage, '\n') && ++i > 0)
	{
		i = read(fd, temp, BUFFER_SIZE);
		if (i == -1 || (i == 0 && 0 == ft_strlen(garbage)))
		{
			if (garbage)
				free(garbage);
			free(temp);
			return (NULL);
		}
		temp[i] = '\0';
		garbage = ft_strjoin(garbage, temp);
		i--;
	}
	free(temp);
	return (garbage);
}

static char	*remove_line(char *garbage)
{
	int		i;
	int		j;
	char	*new_garbage;

	i = 0;
	j = 0;
	while (garbage[i] != '\n' && garbage[i] != '\0')
		i++;
	if (!*garbage)
	{
		free(garbage);
		return (0);
	}
	if (garbage[i] == '\n')
		i++;
	new_garbage = (char *)malloc(sizeof(char) * (ft_strlen(garbage) - i + 1));
	if (!new_garbage)
		return (NULL);
	while (garbage[i] != '\0')
		new_garbage[j++] = garbage[i++];
	new_garbage[j] = '\0';
	free(garbage);
	return (new_garbage);
}

static char	*ft_get_line(char *garbage)
{
	char	*line;
	int		i;
	int		stop;

	i = 0;
	while (garbage[i] != '\n' && garbage[i] != '\0')
		i++;
	if (garbage[i] == '\n')
		i++;
	stop = i;
	line = (char *)malloc(sizeof(char) * (stop + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (i < stop)
	{
		line[i] = garbage[i];
		i++;
	}
	line[stop] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*garbage;	
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	garbage = ft_read_file(garbage, fd);
	if (!garbage || !*garbage)
		return (NULL);
	line = ft_get_line(garbage);
	garbage = remove_line(garbage);
	return (line);
}
