/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingmap___.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 10:23:55 by sakllam           #+#    #+#             */
/*   Updated: 2022/06/11 16:02:48 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	**oldinfos(t_mapelm *map, char *line, int *i)
{
	int	**maping;

	(map->sizey)++;
	maping = malloc(sizeof(int *) * map->sizey);
	if (!maping)
		return (NULL);
	while (map->sizey - *i)
	{
		maping[*i - 1] = map->map[*i - 1];
		(*i)++;
	}
	maping[*i - 1] = malloc(sizeof(int) * (ft_strlen(line) + 1));
	if (!maping[*i - 1])
		return (NULL);
	return (maping);
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
			return (NULL);
		j++;
	}
	maping[i - 1][y] = END;
	if (map->map)
		free(map->map);
	return (maping);
}

int	nomaperror(void)
{
	printf("Error\n");
	printf("No MAP!\n");
	exit (1);
	return (1);
}
