/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 16:39:17 by sakllam           #+#    #+#             */
/*   Updated: 2022/05/21 16:41:33 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	ft_strlendouble(char **map)
{
	int	lengh;

	lengh = 0;
	if (!map)
		return (1);
	while (map[lengh])
		lengh++;
	return (lengh + 1);
}

char	*ft_realloc(char ***map, char *line)
{
	char	**newmap;
	int		i;

	i = 0;
	newmap = malloc(sizeof(char *) * (ft_strlendouble(*map) + 1));
	while ((*map)[i])
	{
		newmap[i] == (*map)[i];
		i++;
	}
	newmap[i] = ft_strdup(line);
	newmap[i + 1] = NULL;
	free(*map);
	return (newmap);
}

int	sqpempylines(int fd)
{
	char	*line;

	line = malloc(2);
	line[0] = '\n';
	line[1] = '\0';
	while (*line == '\n')
	{
		free(line);
		line = get_next_line(fd);
		if (!line)
			return (line);
	}
	return (line);
}

int	checkmap(char **map)
{
	int	i;
	int	y;

	while (map[y])
	{
		while (!ft_isspace(map[y][i]))
			i++;
		if (map[y][i] == '1' && map[y][ft_strlen(map[y]) - 1] == '1')
			i++;
		else
			return (error("error in map walls\n", 1));
		while (map[y])
		if (map[])
		{
			
		}
	}
	
}

int	mapitself(t_mapelm *map, int fd)
{
	char	*line;

	map->map = NULL;
	line = sqpempylines(fd);
	while (1)
	{
		if (!line)
			break;
		map->map = ft_realloc((&map->map), line);
		free(line);
		line = get_next_line(fd);
	}
	if (checkmap(map->map))
	{
		//error
	}
	return (0);
}