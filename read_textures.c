/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 13:45:54 by aqadil            #+#    #+#             */
/*   Updated: 2022/06/07 16:35:57 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	read_north_texture(t_data *mlx)
{
	int	i;
	int	k;
	int	j;

	i = 0;
	k = 0;
	mlx->t_img = mlx_xpm_file_to_image(mlx->mlx, "./textures/redbrick.xpm",
			&mlx->t_w, &mlx->t_h);
	mlx->t_addr = mlx_get_data_addr(mlx->t_img, &mlx->t_bits_per_pixel,
			&mlx->t_line_length, &mlx->t_endian);
	mlx->buff = malloc(4 * mlx->t_h * mlx->t_w);
	while (i < mlx->t_h)
	{
		j = 0;
		while (j < mlx->t_w)
		{
			mlx->buff[k] = get_color(mlx, j, i);
			mlx_pixel_put(mlx->mlx, mlx->win, i, j, mlx->buff[k]);
			j++;
			k++;
		}
		i++;
	}
}

void	read_west_texture(t_data *mlx)
{
	int	i;
	int	k;
	int	j;

	i = 0;
	k = 0;
	mlx->tw_img = mlx_xpm_file_to_image(mlx->mlx, "./textures/skull.xpm",
			&mlx->tw_w, &mlx->tw_h);
	mlx->tw_addr = mlx_get_data_addr(mlx->tw_img, &mlx->tw_bits_per_pixel,
			&mlx->tw_line_length, &mlx->tw_endian);
	mlx->tw_buff = malloc(4 * (mlx->tw_w * mlx->tw_h));
	while (i < mlx->tw_h)
	{
		j = 0;
		while (j < mlx->tw_w)
		{
			mlx->tw_buff[k] = get_color_2(mlx, j, i);
			j++;
			k++;
		}
		i++;
	}
}

void	read_east_texture(t_data *mlx)
{
	int	i;
	int	k;
	int	j;

	i = 0;
	k = 0;
	mlx->te_img = mlx_xpm_file_to_image(mlx->mlx, "./textures/bluestone.xpm",
			&mlx->te_w, &mlx->te_h);
	mlx->te_addr = mlx_get_data_addr(mlx->te_img, &mlx->te_bits_per_pixel,
			&mlx->te_line_length, &mlx->te_endian);
	mlx->te_buff = malloc(mlx->te_h * mlx->te_w * 4);
	while (i < mlx->te_h)
	{
		j = 0;
		while (j < mlx->te_w)
		{
			mlx->te_buff[k] = get_color_3(mlx, j, i);
			j++;
			k++;
		}
		i++;
	}
}

void	read_south_texture(t_data *mlx)
{
	int	i;
	int	k;
	int	j;

	i = 0;
	k = 0;
	mlx->ts_img = mlx_xpm_file_to_image(mlx->mlx, "./textures/pumking.xpm",
			&mlx->ts_w, &mlx->ts_h);
	mlx->ts_addr = mlx_get_data_addr(mlx->ts_img, &mlx->ts_bits_per_pixel,
			&mlx->ts_line_length, &mlx->ts_endian);
	mlx->ts_buff = malloc(4 * mlx->ts_h * mlx->ts_w);
	while (i < mlx->ts_h)
	{
		j = 0;
		while (j < mlx->ts_w)
		{
			mlx->ts_buff[k] = get_color_4(mlx, j, i);
			j++;
			k++;
		}
		i++;
	}
}

void	read_door_texture(t_data *mlx)
{
	int	i;
	int	k;
	int	j;

	i = 0;
	k = 0;
	mlx->door_img = mlx_xpm_file_to_image(mlx->mlx, "./textures/door.xpm",
			&mlx->door_w, &mlx->door_h);
	mlx->door_addr = mlx_get_data_addr(mlx->door_img, &mlx->door_bits_per_pixel,
			&mlx->door_line_length, &mlx->door_endian);
	mlx->door_buff = malloc(4 * (mlx->door_h * mlx->door_w));
	while (i < mlx->door_h)
	{
		j = 0;
		while (j < mlx->door_w)
		{
			mlx->door_buff[k] = get_color_5(mlx, j, i);
			j++;
			k++;
		}
		i++;
	}
}
