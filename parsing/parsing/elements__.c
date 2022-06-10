/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements__.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 10:28:07 by sakllam           #+#    #+#             */
/*   Updated: 2022/06/10 15:15:01 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	getrvals(char *line, t_mapelm *map, int *x)
{
	int	y;
	int	tmpy;

	y = 0;
	while (ft_isdigit(line[*x + y]))
		y++;
	tmpy = y;
	map->floor_color->r[y] = '\0';
	y--;
	while (y >= 0)
	{
		map->floor_color->r[y] = line[*x + y];
		y--;
	}
	*x += tmpy;
}

void	getgvals(char *line, t_mapelm *map, int *x)
{
	int	y;
	int	tmpy;

	y = 0;
	while (ft_isdigit(line[*x + y]))
		y++;
	tmpy = y;
	map->floor_color->g[y] = '\0';
	y--;
	while (y >= 0)
	{
		map->floor_color->g[y] = line[*x + y];
		y--;
	}
	*x += tmpy;
}

void	getbvals(char *line, t_mapelm *map, int *x)
{
	int	y;
	int	tmpy;

	y = 0;
	while (ft_isdigit(line[*x + y]))
		y++;
	tmpy = y;
	map->floor_color->b[y] = '\0';
	y--;
	while (y >= 0)
	{
		map->floor_color->b[y] = line[*x + y];
		y--;
	}
	*x += tmpy;
}

void	floor_color__(char *line, t_mapelm *map, int *i, int x)
{
	int	y;

	if (line[x])
		x++;
	y = 0;
	while (ft_isdigit(line[x + y]))
		y++;
	if (y > 0 && y <= 3 && (line[x + y] == '\n' || line[x + y] == '\0'))
		getbvals(line, map, &x);
	else
	{
		*i = 1;
		return ;
	}
}
