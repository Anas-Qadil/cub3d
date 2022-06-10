/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingmap_.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 18:36:35 by sakllam           #+#    #+#             */
/*   Updated: 2022/06/10 15:15:28 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	error(char *line, int ret)
{
	write(2, "Error\n", 6);
	write(2, line, ft_strlen(line));
	return (ret);
}

int	elementscondictions(char *line)
{
	if (!line)
		return (error("an unexpected eof\n", 0));
	if (*line == '\n')
		return (-1);
	if (line[0] == 'N' && line[1] == 'O' && !ft_isspace(line[2]))
		return (1);
	if (line[0] == 'S' && line[1] == 'O' && !ft_isspace(line[2]))
		return (2);
	if (line[0] == 'W' && line[1] == 'E' && !ft_isspace(line[2]))
		return (3);
	if (line[0] == 'E' && line[1] == 'A' && !ft_isspace(line[2]))
		return (4);
	if (line[0] == 'F' && !ft_isspace(line[1]))
		return (5);
	if (line[0] == 'C' && !ft_isspace(line[1]))
		return (6);
	return (error("no such element as the one found\n", 0));
}

int	get_elementsvals__(char *line, t_mapelm *map, int *x, int i)
{
	if (elementscondictions(line) == 1)
	{
		(*x)++;
		north_texure(line, map, &i);
		if (i)
			return (error("north texure error", i));
	}
	if (elementscondictions(line) == 2)
	{
		(*x)++;
		south_texure(line, map, &i);
		if (i)
			return (error("south texure error", i));
	}
	if (elementscondictions(line) == 3)
	{
		(*x)++;
		west_texure(line, map, &i);
		if (i)
			return (error("west texure error", i));
	}
	return (i);
}

int	get_elementsvals_(char *line, t_mapelm *map, int *x, int i)
{
	if (elementscondictions(line) == 4)
	{
		(*x)++;
		east_texure(line, map, &i);
		if (i)
			return (error("north texure error", i));
	}
	if (elementscondictions(line) == 5)
	{
		(*x)++;
		floor_color(line, map, &i);
		if (i)
			return (error("floor color error", i));
	}
	if (elementscondictions(line) == 6)
	{
		(*x)++;
		ceilling_color(line, map, &i);
		if (i)
			return (error("ceilling color error", i));
	}
	return (i);
}

int	get_elementsvals(char *line, t_mapelm *map, int *x)
{
	int	i;

	i = 0;
	i = get_elementsvals_(line, map, x, i);
	i = get_elementsvals__(line, map, x, i);
	return (i);
}
