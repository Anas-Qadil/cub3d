/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 14:05:04 by aqadil            #+#    #+#             */
/*   Updated: 2022/06/07 10:05:38 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int map[11][15];

int	get_player_y_pos(t_data *mlx)
{
	int i = 0;
	int found = 0;
	
	while (i < mlx->mapY)
	{
		int j = 0;
		while (j < mlx->mapX)
		{
			if (map[i][j] == NORTH || map[i][j] == SOUTH  || map[i][j] == EAST  || map[i][j] == WEST)
			{
				found = i;
				break ;
			}
			j++;
		}
		if (found != 0)
			break;
		i++;
	}
	return ((found * 64) + 20);	
}

int	get_player_x_pos(t_data *mlx)
{
	int i = 0;
	int found = 0;
	
	while (i < mlx->mapY)
	{
		int j = 0;
		while (j < mlx->mapX)
		{
			if (map[i][j] == NORTH || map[i][j] == SOUTH  || map[i][j] == EAST  || map[i][j] == WEST)
			{
				found = j;
				break ;
			}
			j++;
		}
		if (found != 0)
			break;
		i++;
	}
	return ((found * 64) + 20);	
}