/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 23:51:57 by sakllam           #+#    #+#             */
/*   Updated: 2022/05/12 16:38:34 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

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
		if (!line || !elementscondictions(line) || get_elementsvals(line, map, &i))
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

int	mapreading(t_mapelm *map, char *name)
{
	int	fd;

	fd = openfile(name, map);
	if (mapreadingelements(map, fd))
		return (1);
	if (mapitself(map, fd))
		return (1);
}

t_mapelm	*parsingmap(char *name)
{
	int			width;
	int			heigh;
	t_mapelm	*map;

	map =  malloc(sizeof(t_mapelm));
	if (mapreading(map, name))
	{
		free(map);
		exit(1);
	}
}