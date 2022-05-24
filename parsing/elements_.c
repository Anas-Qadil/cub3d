/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 22:46:40 by sakllam           #+#    #+#             */
/*   Updated: 2022/05/11 23:59:37 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

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
	map->floor_color.r[y] = '\0';
	y--;
	while (y >= 0)
	{
		map->floor_color.r[y] = line[*x + y];
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
	map->floor_color.r[y] = '\0';
	y--;
	while (y >= 0)
	{
		map->floor_color.r[y] = line[*x + y];
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
	map->floor_color.r[y] = '\0';
	y--;
	while (y >= 0)
	{
		map->floor_color.r[y] = line[*x + y];
		y--;
	}
	*x += tmpy;
}

void	floor_color__(char *line, t_mapelm *map ,int *i, int x)
{
	int	y;

	y = 0;
	while (ft_isdigit(line[x + y]))
		y++;
	if (y == 0 && y <= 3 && line[x + y] == '\n')
		getbvals(line, map, &x);
	else
	{
		*i = 1;
		return ;
	}
}

void	floor_color_(char *line, t_mapelm *map ,int *i, int x)
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
	while (ft_isdigit(line[x + y]))
		y++;
	if (y == 0 && y <= 3 && line[x + y] == ',')
		getgvals(line, map, &x);
	else
	{
		*i = 1;
		return ;
	}
	floor_color__(line, map ,i,x);
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

	r = ft_atoi(map->floor_color.r);
	if (!(r >= 0 && r <= 255))
	{
		*i = 1;
		return ;
	}
	g = ft_atoi(map->floor_color.g);
	if (!(g >= 0 && g <= 255))
	{
		*i = 1;
		return ;
	}
	b = ft_atoi(map->floor_color.b);
	if (!(b >= 0 && b <= 255))
	{
		*i = 1;
		return ;
	}
	map->floor_color_ = 256^2* r + 256* g + b;
}

void	floor_color(char *line, t_mapelm *map ,int *i)
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
	floor_color_(line, map ,i, x);
	if (*i)
		return ;
	convertandcheckfloor(map, i);
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

void	getgvals_(char *line, t_mapelm *map, int *x)
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

void	getbvals_(char *line, t_mapelm *map, int *x)
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

void	ceilling_color__(char *line, t_mapelm *map ,int *i, int x)
{
	int	y;

	y = 0;
	while (ft_isdigit(line[x + y]))
		y++;
	if (y == 0 && y <= 3 && line[x + y] == '\n')
		getbvals_(line, map, &x);
	else
	{
		*i = 1;
		return ;
	}
}

void	ceilling_color_(char *line, t_mapelm *map ,int *i, int x)
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
	while (ft_isdigit(line[x + y]))
		y++;
	if (y == 0 && y <= 3 && line[x + y] == ',')
		getgvals_(line, map, &x);
	else
	{
		*i = 1;
		return ;
	}
	ceilling_color__(line, map ,i,x);
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
	map->ceilling_color_ = 256^2* r + 256* g + b;
}

void	ceilling_color(char *line, t_mapelm *map ,int *i)
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
	ceilling_color_(line, map ,i, x);
	if (*i)
		return ;
	convertandcheckceilling(map, i);
	if (*i)
		return ;
}