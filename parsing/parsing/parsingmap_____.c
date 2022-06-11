/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingmap_____.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 10:25:39 by sakllam           #+#    #+#             */
/*   Updated: 2022/06/11 12:20:27 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	top_isntawall(t_mapelm *map)
{
	int	i;

	i = 0;
	while (map->map[0][i] != END)
	{
		if (map->map[0][i] != WALL)
			return (1);
		i++;
	}
	return (0);
}

int	buttom_isntawall(t_mapelm *map)
{
	int	i;

	i = 0;
	while (map->map[map->sizey - 1][i] != END)
	{
		if (map->map[map->sizey - 1][i] != WALL)
			return (1);
		i++;
	}
	return (0);
}

int	wallsurrounding(t_mapelm *map)
{
	if (top_isntawall(map))
	{
		printf("Error\n");
		printf("top line is not a wall\n");
		exit (1);
	}
	if (buttom_isntawall(map))
	{
		printf("Error\n");
		printf("line at the end is not a wall\n");
		exit (1);
	}
	if (right_isntwall(map))
	{
		printf("Error\n");
		printf("right line is not a wall\n");
		exit (1);
	}
	if (leftisntwall(map))
	{
		printf("Error\n");
		exit (printf("left line is not a wall\n"));
	}
	return (0);
}

int	multipositions(t_mapelm *map)
{
	int	i;
	int	pos;
	int	j;

	pos = 0;
	i = 0;
	while (map->sizey > i)
	{
		j = 0;
		while (map->map[i][j] != END)
		{
			if (map->map[i][j] == NORTH || map->map[i][j] == EAST
			|| map->map[i][j] == SOUTH || map->map[i][j] == WEST)
			pos++;
			j++;
		}
		i++;
	}
	if (pos == 0 || pos > 1)
	{
		printf ("Error\n");
		printf ("check start position\n");
		exit (1);
	}
	return (0);
}

int	nextandperv(t_mapelm *map, int i, int j)
{
	if (map->map[i][j - 1] == WALL && map->map[i][j + 1] == WALL)
		return (0);
	return (1);
}
