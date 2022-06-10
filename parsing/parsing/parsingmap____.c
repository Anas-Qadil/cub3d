/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingmap____.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 10:24:40 by sakllam           #+#    #+#             */
/*   Updated: 2022/06/10 15:15:19 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	mapandcheck(t_mapelm *map, int fd)
{
	char	*line;
	int		i;

	i = 1;
	line = sqpempty(fd);
	if (!line)
		return (nomaperror());
	map->sizey = 0;
	while (1)
	{
		if (!line)
			break ;
		map->map = ft_realocmap(map, line, i);
		if (!map->map)
		{
			printf("Error\n");
			printf("unexpected map line\n");
			return (1);
		}
		line = get_next_line(fd);
	}
	return (0);
}

int	getlastone(t_mapelm *map, int i)
{
	int	j;

	j = 0;
	while (map->map[i][j] != END)
		j++;
	return (j - 1);
}

int	right_isntwall(t_mapelm *map)
{
	int	i;

	i = 0;
	while (i < map->sizey)
	{
		if (map->map[i][0] != WALL)
			return (1);
		i++;
	}
	return (0);
}

int	leftisntwallextra(int j, int *lastlinesize, t_mapelm *map, int i)
{
	int	tmpj;

	if ((*lastlinesize) > j)
	{
		while ((*lastlinesize) >= j)
		{
			if (map->map[i - 1][(*lastlinesize)] != WALL)
				return (1);
			(*lastlinesize)--;
		}
		(*lastlinesize) = j;
	}
	else if ((*lastlinesize) < j)
	{
		tmpj = j;
		while ((*lastlinesize) <= j)
		{
			if (map->map[i][j] != WALL)
				return (1);
			j--;
		}
		(*lastlinesize) = tmpj;
	}
	return (0);
}

int	leftisntwall(t_mapelm *map)
{
	int	i;
	int	j;
	int	lastlinesize;

	i = 0;
	while (i < map->sizey)
	{
		j = 0;
		while (map->map[i][j] != END)
			j++;
		if (i == 0)
			lastlinesize = j - 1;
		if (map->map[i][j - 1] != WALL)
			return (1);
		if (leftisntwallextra(j - 1, &lastlinesize, map, i))
			return (1);
		i++;
	}
	return (0);
}
