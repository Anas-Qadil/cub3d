/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing__.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 10:46:17 by sakllam           #+#    #+#             */
/*   Updated: 2022/06/11 12:24:51 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	ft_lenghdoubleint(int **x, int max)
{
	int	i;
	int	j;
	int	size;

	size = 0;
	i = 0;
	while (i < max)
	{
		j = 0;
		while (x[i][j] != END)
		{
			size++;
			j++;
		}
		i++;
	}
	return (size);
}

void	demchanging(t_mapelm *map)
{
	int	i;
	int	j;
	int	size;

	size = 0;
	i = 0;
	while (i < map->sizey)
	{
		j = 0;
		while (map->map[i][j] != END)
		{
			map->mapone[size] = map->map[i][j];
			size++;
			j++;
		}
		i++;
	}
	map->mapone[size] = END;
}

int	sizeofit(t_mapelm *map)
{
	int	i;
	int	y;
	int	size;

	i = 0;
	size = 0;
	while (i < map->sizey)
	{
		y = 0;
		while (map->map[i][y] != END)
			y++;
		if (y > size)
			size = y;
		i++;
	}
	return (size);
}

int	**freetosavelines(int i, int ***maping, t_mapelm *map)
{
	printf("Error\n");
	printf("Malloc error\n");
	exit (1);
	return (NULL);
}
