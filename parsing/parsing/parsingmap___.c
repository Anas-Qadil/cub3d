/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingmap___.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 10:23:55 by sakllam           #+#    #+#             */
/*   Updated: 2022/06/10 15:15:22 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	**ft_freeforfree(t_mapelm *map)
{
	int	i;

	i = 0;
	while (i < map->sizey - 1)
	{
		free (map->map[i]);
		i++;
	}
	free(map->map);
	map->map = NULL;
	(map->sizey)--;
	return (NULL);
}

int	**oldinfos(t_mapelm *map, char *line, int *i)
{
	int	**maping;

	(map->sizey)++;
	maping = malloc(sizeof(int *) * map->sizey);
	if (!maping)
		return (ft_freeforfree(map));
	while (map->sizey - *i)
	{
		maping[*i - 1] = map->map[*i - 1];
		(*i)++;
	}
	maping[*i - 1] = malloc(sizeof(int) * (ft_strlen(line) + 1));
	if (!maping[*i - 1])
		return (ft_freeforfree(map));
	return (maping);
}

int	**optimizeelse(t_mapelm *map, char *line, int *x, int **y)
{
	free (line);
	free(y);
	free (x);
	return (ft_freeforfree(map));
}

int	**ft_realocmap(t_mapelm *map, char *line, int i)
{
	int	**maping;
	int	j;
	int	y;

	y = 0;
	j = 0;
	maping = oldinfos(map, line, &i);
	if (!maping)
		return (NULL);
	while (line[j])
	{
		if (castchartoint(line[0]) != NLINE && castchartoint(line[j]) != 404)
		{
			if (castchartoint(line[j]) != NLINE
				&& castchartoint(line[j]) != SPACES)
				maping[i - 1][y++] = castchartoint(line[j]);
		}
		else
			return (optimizeelse(map, line, maping[i - 1], maping));
		j++;
	}
	maping[i - 1][y] = END;
	free(map->map);
	return (maping);
}

int	nomaperror(void)
{
	printf("Error\n");
	printf("No MAP!\n");
	return (1);
}
