/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 15:10:50 by aqadil            #+#    #+#             */
/*   Updated: 2022/06/02 18:03:33 by aqadil           ###   ########.fr       */
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
		if (map[var.ipy][var.ipx_add_xo] == 0 || map[var.ipy][var.ipx_add_xo] == NORTH)
			mlx->px += mlx->pdx * 4 * mlx->move_up;
		if (map[var.ipy_add_yo][var.ipx] == 0 || map[var.ipy_add_yo][var.ipx] == NORTH )
			mlx->py += mlx->pdy * 4 * mlx->move_up;
		mlx->move_down = 0;
	}
	if (mlx->move_down == 1)
	{
		if (map[var.ipy][var.ipx_sub_xo] == 0 || map[var.ipy][var.ipx_sub_xo] == NORTH)
			mlx->px -= mlx->pdx * 4;
		if (map[var.ipy_sub_yo][var.ipx] == 0 || map[var.ipy_sub_yo][var.ipx] == NORTH)
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

int	render(t_data *mlx)
{
	update_everything(mlx);
	draw_everything(mlx);
	return (1);
}