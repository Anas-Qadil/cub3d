/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 22:46:40 by sakllam           #+#    #+#             */
/*   Updated: 2022/06/10 15:15:03 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	ceilling_color_(char *line, t_mapelm *map, int *i, int x)
{
	int	y;

	y = 0;
	while (ft_isdigit(line[x + y]))
		y++;
	if (y > 0 && y <= 3 && line[x + y] == ',')
		getrvals_(line, map, &x);
	else
	{
		*i = 1;
		return ;
	}
	y = 0;
	if (line[x])
		x++;
	while (ft_isdigit(line[x + y]))
		y++;
	if (y > 0 && y <= 3 && line[x + y] == ',')
		getgvals_(line, map, &x);
	else
	{
		*i = 1;
		return ;
	}
	ceilling_color__(line, map, i, x);
}

void	convertandcheckceilling(t_mapelm *map, int *i)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(map->ceilling_color.r);
	if (!(r >= 0 && r <= 255))
	{
		*i = 1;
		return ;
	}
	g = ft_atoi(map->ceilling_color.g);
	if (!(g >= 0 && g <= 255))
	{
		*i = 1;
		return ;
	}
	b = ft_atoi(map->ceilling_color.b);
	if (!(b >= 0 && b <= 255))
	{
		*i = 1;
		return ;
	}
	map->ceilling_color_ = 256 * 256 * r + 256 * g + b;
}

void	ceilling_color(char *line, t_mapelm *map, int *i)
{
	int	x;

	x = 1;
	while (!ft_isspace(line[x]))
		x++;
	if (!line[x])
	{
		*i = 1;
		return ;
	}
	ceilling_color_(line, map, i, x);
	if (*i)
		return ;
	convertandcheckceilling(map, i);
	if (*i)
		return ;
}
