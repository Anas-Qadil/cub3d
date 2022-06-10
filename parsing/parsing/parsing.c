/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 23:37:11 by sakllam           #+#    #+#             */
/*   Updated: 2022/06/10 15:15:12 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	maponedem(t_mapelm *map)
{
	int	size;

	map->map = mapfinal(map);
	if (!(map->map))
		return (1);
	size = ft_lenghdoubleint(map->map, map->sizey);
	map->mapone = malloc(sizeof(int) * (size + 1));
	if (!map->mapone)
	{
		printf("Error\n");
		printf("Malloc error\n");
		return (1);
	}
	demchanging(map);
	return (0);
}

t_mapelm	*parsing(char *argv)
{
	int			fd;
	t_mapelm	*map;

	fd = accessingallowed(argv);
	close (fd);
	map = parsingmap(argv);
	maponedem(map);
	return (map);
}
