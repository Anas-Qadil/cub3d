/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements___.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 10:29:00 by sakllam           #+#    #+#             */
/*   Updated: 2022/06/10 15:14:59 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	floor_color_(char *line, t_mapelm *map, int *i, int x)
{
	int	y;

	y = 0;
	while (ft_isdigit(line[x + y]))
		y++;
	if (y > 0 && y <= 3 && line[x + y] == ',')
		getrvals(line, map, &x);
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
		getgvals(line, map, &x);
	else
	{
		*i = 1;
		return ;
	}
	floor_color__(line, map, i, x);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	s;
	int	res;

	i = 0;
	res = i;
	s = 1;
	while (nptr[i] == ' ' || nptr[i] == '\n' || nptr[i] == '\f'
		|| nptr[i] == '\t' || nptr[i] == '\v' || nptr[i] == '\r')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			s = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9' && nptr[i])
	{
		res *= 10;
		res += nptr[i] - '0';
		i++;
	}
	return (res * s);
}

void	convertandcheckfloor(t_mapelm *map, int *i)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(map->floor_color->r);
	if (!(r >= 0 && r <= 255))
	{
		*i = 1;
		return ;
	}
	g = ft_atoi(map->floor_color->g);
	if (!(g >= 0 && g <= 255))
	{
		*i = 1;
		return ;
	}
	b = ft_atoi(map->floor_color->b);
	if (!(b >= 0 && b <= 255))
	{
		*i = 1;
		return ;
	}
	map->floor_color_ = 256 * 256 * r + 256 * g + b;
}

void	floor_color(char *line, t_mapelm *map, int *i)
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
	map->floor_color = malloc(sizeof(t_rgbcolor));
	if (!map->floor_color)
	{
		*i = 1;
		return ;
	}
	floor_color_(line, map, i, x);
	if (*i)
		return ;
	convertandcheckfloor(map, i);
	if (*i)
		return ;
}

void	getrvals_(char *line, t_mapelm *map, int *x)
{
	int	y;
	int	tmpy;

	y = 0;
	while (ft_isdigit(line[*x + y]))
		y++;
	tmpy = y;
	map->ceilling_color.r[y] = '\0';
	y--;
	while (y >= 0)
	{
		map->ceilling_color.r[y] = line[*x + y];
		y--;
	}
	*x += tmpy;
}
