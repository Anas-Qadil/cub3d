/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_v3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:49:36 by aqadil            #+#    #+#             */
/*   Updated: 2022/06/07 20:54:40 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int map[11][15];

void	open_textures(t_data *mlx)
{
	mlx->t_path = "./textures/redbrick.xpm";
	mlx->ts_path = "./textures/banner.xpm";
	mlx->te_path = "./textures/bluestone.xpm";
	mlx->tw_path = "./textures/skull.xpm";
	mlx->door_path = "./textures/door.xpm";
}

void	read_home_image(t_data *mlx)
{
	int	w;
	int	h;

	mlx->home_img = mlx_xpm_file_to_image(mlx->mlx,
			"./textures/CUB3d.xpm", &w, &h);
	mlx->home_addr = mlx_get_data_addr(mlx->home_img,
			&mlx->bits_per_pixel, &mlx->home_line_length, &mlx->home_endian);
	mlx->home_w = w;
	mlx->home_h = h;
	mlx->press_img = mlx_xpm_file_to_image(mlx->mlx,
			"./textures/press.xpm", &w, &h);
	mlx->press_addr = mlx_get_data_addr(mlx->press_img,
			&mlx->bits_per_pixel, &mlx->press_line_length, &mlx->press_endian);
	mlx->press_w = w;
	mlx->press_h = h;
	mlx->loading_img = mlx_new_image(mlx->mlx, mlx->loading_w, mlx->loading_h);
	mlx->loading_addr = mlx_get_data_addr(mlx->loading_img,
			&mlx->loading_bits_per_pixel,
			&mlx->loading_line_length, &mlx->loading_endian);
}

int	get_player_direction(t_data *mlx)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < mlx->map_y)
	{
		j = 0;
		while (j < mlx->map_x)
		{
			if (map[i][j] == NORTH)
				mlx->pa = 90;
			if (map[i][j] == EAST)
				mlx->pa = 0;
			if (map[i][j] == SOUTH)
				mlx->pa = 270;
			if (map[i][j] == WEST)
				mlx->pa = 180;
			j++;
		}
		i++;
	}
	return (0);
}

void	draw_loading(t_data *mlx)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (mlx->loading_i < 1)
	{
		while (mlx->loading_j < mlx->loading_w)
		{
			my_mlx_pixel_put_loading(mlx, mlx->loading_j,
				mlx->loading_i, 0x00FFFFFF);
			mlx->loading_j++;
			if (mlx->loading_j % 2 == 0)
				break ;
		}
		if (mlx->loading_j >= mlx->loading_w - 1)
		{
			mlx->loading_i++;
			mlx->isloadingdone = 1;
		}
		if (mlx->loading_j % 2 == 0)
			break ;
	}
}
