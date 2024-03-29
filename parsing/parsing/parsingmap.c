/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 23:51:57 by sakllam           #+#    #+#             */
/*   Updated: 2022/06/11 19:36:32 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	checkupanddown(t_mapelm *map, int i, int j)
{
	if (map->map[i + 1][j] == WALL && map->map[i - 1][j] == WALL)
		return (0);
	return (1);
}

int	doorschecking(t_mapelm *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->sizey)
	{
		j = 0;
		while (map->map[i][j] != END)
		{
			if (map->map[i][j] == DOOR)
			{
				if (checkupanddown(map, i, j) != 0
					&& nextandperv(map, i, j) != 0)
				{
					printf("Error\n");
					printf("Doors are not in them place\n");
					exit (1);
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	checkvalmap(t_mapelm *map)
{
	int	i;
	int	startpos;

	i = 0;
	startpos = 1;
	if (map->sizey < 3)
	{
		printf("Error\n");
		printf("Error walls are not surrounding | lines number too small\n");
		exit (1);
	}
	if (wallsurrounding(map))
		exit (1);
	if (multipositions(map))
		exit (1);
	if (doorschecking(map))
		exit (1);
	return (0);
}

int	mapreading(t_mapelm *map, char *name)
{
	int	fd;

	fd = openfile(name, map);
	if (mapreadingelements(map, fd))
		exit (1);
	if (mapandcheck(map, fd))
		exit (1);
	close (fd);
	if (checkvalmap(map))
		exit (1);
	return (0);
}

t_mapelm	*parsingmap(char *name)
{
	t_mapelm	*map;

	map = malloc(sizeof(t_mapelm));
	map->map = NULL;
	map->wf = 0;
	map->cf = 0;
	map->nf = 0;
	map->ef = 0;
	map->sf = 0;
	map->ff = 0;
	if (mapreading(map, name))
		exit(1);
	return (map);
}
