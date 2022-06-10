/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 10:27:20 by sakllam           #+#    #+#             */
/*   Updated: 2022/06/10 18:53:42 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	*ft_allocateit(int *line, int size)
{
	int	*new;
	int	i;

	new = malloc(sizeof(int) * (size + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (line[i] != END)
	{
		new[i] = line[i];
		i++;
	}
	while (size > i)
	{
		new[i] = WALL;
		i++;
	}
	new[i] = END;
	return (new);
}

void	freemap(t_mapelm *map)
{
	int	i;

	i = 0;
	while (i < map->sizey)
	{
		free (map->map[i]);
		i++;
	}
	free (map->map);
	map->map = NULL;
}

int	**mapfinal(t_mapelm *map)
{
	int	**maping;
	int	i;

	i = 0;
	maping = malloc(sizeof(int *) * map->sizey);
	if (!maping)
		return (NULL);
	map->sizex = sizeofit(map);
	while (i < map->sizey)
	{
		maping[i] = ft_allocateit(map->map[i], map->sizex);
		if (!maping[i])
			return (freetosavelines(i, &maping, map));
		i++;
	}
	freemap(map);
	return (maping);
}
