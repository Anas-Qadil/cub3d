/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_v3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:49:36 by aqadil            #+#    #+#             */
/*   Updated: 2022/06/07 18:07:34 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int map[11][15];

void	read_home_image(t_data *mlx)
{
	int	w;
	int	h;

	mlx->HOME_img = mlx_xpm_file_to_image(mlx->mlx,
			"./textures/CUB3d.xpm", &w, &h);
	mlx->HOME_addr = mlx_get_data_addr(mlx->HOME_img,
			&mlx->bits_per_pixel, &mlx->HOME_line_length, &mlx->HOME_endian);
	mlx->HOME_w = w;
	mlx->HOME_h = h;
	mlx->PRESS_img = mlx_xpm_file_to_image(mlx->mlx,
			"./textures/Press.xpm", &w, &h);
	mlx->PRESS_addr = mlx_get_data_addr(mlx->PRESS_img,
			&mlx->bits_per_pixel, &mlx->PRESS_line_length, &mlx->PRESS_endian);
	mlx->PRESS_w = w;
	mlx->PRESS_h = h;
	mlx->LOADING_img = mlx_new_image(mlx->mlx, mlx->LOADING_w, mlx->LOADING_h);
	mlx->LOADING_addr = mlx_get_data_addr(mlx->LOADING_img,
			&mlx->LOADING_bits_per_pixel,
			&mlx->LOADING_line_length, &mlx->LOADING_endian);
}

int	get_player_direction(t_data *mlx)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < mlx->mapY)
	{
		j = 0;
		while (j < mlx->mapX)
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
	while (mlx->LOADING_i < 1)
	{
		while (mlx->LOADING_j < mlx->LOADING_w)
		{
			my_mlx_pixel_put_loading(mlx, mlx->LOADING_j,
				mlx->LOADING_i, 0x00FFFFFF);
			mlx->LOADING_j++;
			if (mlx->LOADING_j % 2 == 0)
				break ;
		}
		if (mlx->LOADING_j >= mlx->LOADING_w - 1)
		{
			mlx->LOADING_i++;
			mlx->isLoadingDone = 1;
		}
		if (mlx->LOADING_j % 2 == 0)
			break ;
	}
}
