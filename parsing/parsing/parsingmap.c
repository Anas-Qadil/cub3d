/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 23:51:57 by sakllam           #+#    #+#             */
/*   Updated: 2022/06/10 15:15:30 by aqadil           ###   ########.fr       */
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
					return (1);
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
		return (1);
	}
	if (wallsurrounding(map))
		return (1);
	if (multipositions(map))
		return (1);
	if (doorschecking(map))
		return (1);
	return (0);
}

int	mapreading(t_mapelm *map, char *name)
{
	int	fd;

	fd = openfile(name, map);
	if (mapreadingelements(map, fd))
		return (1);
	if (mapandcheck(map, fd))
		return (1);
	close (fd);
	if (checkvalmap(map))
		return (1);
	return (0);
}




t_mapelm	*parsingmap(char *name)
{
	t_mapelm	*map;
	int			i;

	map = malloc(sizeof(t_mapelm));
	map->floor_color = NULL;
	map->map = NULL;
	map->north_texure = NULL;
	map->south_texure = NULL;
	map->east_texure = NULL;
	map->west_texure = NULL;
	if (mapreading(map, name))
	{
		i = 0;
		free(map->floor_color);
		while (map->map && i < map->sizey)
		{
			free(map->map[i]);
			i++;
		}
		free(map->map);
		map->map = NULL; 
		free(map->north_texure);
		free(map->south_texure);
		free(map->east_texure);
		free(map->west_texure);
		free(map);
		while (1);
		exit(1);
	}
	return (map);
}
