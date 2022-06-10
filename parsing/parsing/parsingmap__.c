/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingmap__.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 10:22:57 by sakllam           #+#    #+#             */
/*   Updated: 2022/06/10 15:15:25 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	openfile(char *name, t_mapelm *map)
{
	int	fd;

	fd = open(name, O_RDONLY);
	if (fd >= 0)
		return (fd);
	perror("cube3d:");
	free(map);
	exit (0);
}

int	ft_isspace(char x)
{
	if (x == '\t' || x == '\n' || x == '\v'
		|| x == '\f' || x == '\r' || x == ' ')
		return (0);
	return (1);
}

int	mapreadingelements(t_mapelm *map, int fd)
{
	char	*line;
	int		i;

	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!elementscondictions(line) || get_elementsvals(line, map, &i))
		{
			free (line);
			return (1);
		}
		free(line);
		if (i == 6)
			break ;
	}
	return (0);
}

char	*sqpempty(int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!(line && ft_strlen(line) == 1 && line[0] == '\n'))
			break ;
		free (line);
	}
	return (line);
}

int	castchartoint(char alpha)
{
	if (alpha == '1')
		return (WALL);
	else if (alpha == ' ')
		return (WALL);
	else if (alpha == '0')
		return (FLOOR);
	else if (alpha == 'D')
		return (DOOR);
	else if (alpha == 'W')
		return (WEST);
	else if (alpha == 'S')
		return (SOUTH);
	else if (alpha == 'N')
		return (NORTH);
	else if (alpha == 'E')
		return (EAST);
	else if (alpha == '\n')
		return (NLINE);
	else
		return (ERROR);
}
