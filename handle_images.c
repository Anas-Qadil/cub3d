/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 13:58:24 by aqadil            #+#    #+#             */
/*   Updated: 2022/06/10 10:50:39 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_images(t_data *mlx)
{
	int	w;
	int	h;

	w = mlx->map_x * 16;
	h = mlx->map_y * 16;
	mlx->img = mlx_new_image(mlx->mlx, w, h);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	mlx->cast_img = mlx_new_image(mlx->mlx, mlx->win_x, mlx->win_y);
	mlx->cast_addr = mlx_get_data_addr(mlx->cast_img, &mlx->cast_bits_per_pixel,
			&mlx->cast_line_length, &mlx->cast_endian);
	mlx->player_img = mlx_new_image(mlx->mlx, 5, 5);
	mlx->player_addr = mlx_get_data_addr(mlx->player_img,
			&mlx->player_bits_per_pixel, &mlx->player_line_length,
			&mlx->player_endian);
}
