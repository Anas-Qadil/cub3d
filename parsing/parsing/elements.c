/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 22:32:50 by sakllam           #+#    #+#             */
/*   Updated: 2022/06/11 18:01:45 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*p;

	i = 0;
	p = (char *) malloc(ft_strlen(s) + 1);
	if (!p)
		return (0);
	while (s[i])
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

void	north_texure(char *line, t_mapelm *map, int *i)
{
	int	x;

	x = 2;
	while (!ft_isspace(line[x]))
		x++;
	if (!line[x])
	{
		return ;
		*i = 1;
	}
	map->north_texure = ft_strdup_(&line[x]);
}

void	south_texure(char *line, t_mapelm *map, int *i)
{
	int	x;

	x = 2;
	while (!ft_isspace(line[x]))
		x++;
	if (!line[x])
	{
		return ;
		*i = 1;
	}
	map->south_texure = ft_strdup_(&line[x]);
}

void	west_texure(char *line, t_mapelm *map, int *i)
{
	int	x;

	x = 2;
	map->wf = 1;
	while (!ft_isspace(line[x]))
		x++;
	if (!line[x])
	{
		return ;
		*i = 1;
	}
	map->west_texure = ft_strdup_(&line[x]);
}

void	east_texure(char *line, t_mapelm *map, int *i)
{
	int	x;

	x = 2;
	while (!ft_isspace(line[x]))
		x++;
	if (!line[x])
	{
		return ;
		*i = 1;
	}
	map->east_texure = ft_strdup_(&line[x]);
}
