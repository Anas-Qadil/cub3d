/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 15:10:50 by aqadil            #+#    #+#             */
/*   Updated: 2022/06/02 21:18:30 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int map[11][15];

void	update_everything(t_data *mlx)
{
	t_keyvars var;

	keycode_init(&var, mlx);
	if (mlx->move_left == 1)
		mlx->pa += 0.2 * 8 * mlx->move_left;
	else
		mlx->pa -= 0.2 * 8 * mlx->move_right;
	mlx->pa = FixAng(mlx->pa);
	mlx->pdx = cos(degToRad(mlx->pa));
	mlx->pdy = -sin(degToRad(mlx->pa));
	if (mlx->move_up == 1)
	{
		if (map[var.ipy][var.ipx_add_xo] == 0 || map[var.ipy][var.ipx_add_xo] == NORTH || map[var.ipy][var.ipx_add_xo] == DOOR_CLOSED)
			mlx->px += mlx->pdx * 4 * mlx->move_up;
		if (map[var.ipy_add_yo][var.ipx] == 0 || map[var.ipy_add_yo][var.ipx] == NORTH || map[var.ipy_add_yo][var.ipx] == DOOR_CLOSED)
			mlx->py += mlx->pdy * 4 * mlx->move_up;
		mlx->move_down = 0;
	}
	if (mlx->move_down == 1)
	{
		if (map[var.ipy][var.ipx_sub_xo] == 0 || map[var.ipy][var.ipx_sub_xo] == NORTH || map[var.ipy][var.ipx_sub_xo] == DOOR_CLOSED)
			mlx->px -= mlx->pdx * 4;
		if (map[var.ipy_sub_yo][var.ipx] == 0 || map[var.ipy_sub_yo][var.ipx] == NORTH || map[var.ipy_sub_yo][var.ipx] == DOOR_CLOSED)
			mlx->py -= mlx->pdy * 4;
		mlx->move_up = 0;
	}
}

void	read_textures(t_data *mlx)
{
	read_north_texture(mlx);
	read_west_texture(mlx);
	read_east_texture(mlx);
	read_south_texture(mlx);
	read_door_texture(mlx);
}

void	check_doors(t_data *mlx)
{
	int i = 0;
	int j = 0;

	while (i < mlx->mapY)
	{
		j = 0;
		while (j < mlx->mapX)
		{
			if (map[i][j] == DOOR_CLOSED)
				map[i][j] = DOOR;
			j++;
		}
		i++;
	}
}

int	render(t_data *mlx)
{
	update_everything(mlx);
	draw_everything(mlx);
	mlx->start++;
	if (mlx->start == 100)
		check_doors(mlx);
	return (1);
}