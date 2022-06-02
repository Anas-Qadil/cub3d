/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 13:45:54 by aqadil            #+#    #+#             */
/*   Updated: 2022/06/02 14:02:02 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    read_north_texture(t_data *mlx)
{
	int i = 0;
	int k = 0;
    int w, h;
    
    mlx->t_img = mlx_xpm_file_to_image(mlx->mlx, "./textures/redbrick.xpm", &w, &h);
	mlx->t_addr = mlx_get_data_addr(mlx->t_img, &mlx->t_bits_per_pixel, &mlx->t_line_length, &mlx->t_endian);
	while (i < 64)
	{
		int j = 0;
		while (j < 64)
		{
			mlx->buff[k] = get_color(mlx, j, i);
			j++;
			k++;
		}
		i++;
	}
}

void    read_west_texture(t_data *mlx)
{
    int i;
	int k;
    int w;
    int h;
    int j;
    
	i = 0;
	k = 0;
    mlx->tw_img = mlx_xpm_file_to_image(mlx->mlx, "./textures/wall2.xpm", &w, &h);
	mlx->tw_addr = mlx_get_data_addr(mlx->tw_img, &mlx->tw_bits_per_pixel, &mlx->tw_line_length, &mlx->tw_endian);
	while (i < 64)
	{
		j = 0;
		while (j < 64)
		{
			mlx->tw_buff[k] = get_color_2(mlx, j, i);
			j++;
			k++;
		}
		i++;
	}
}

void    read_east_texture(t_data *mlx)
{
    int i;
	int k;
    int w;
    int h;
    int j;
    
	i = 0;
	k = 0;
    
    mlx->te_img = mlx_xpm_file_to_image(mlx->mlx, "./textures/EA.xpm", &w, &h);
	mlx->te_addr = mlx_get_data_addr(mlx->te_img, &mlx->te_bits_per_pixel, &mlx->te_line_length, &mlx->te_endian);
	while (i < 64)
	{
		j = 0;
		while (j < 64)
		{
			mlx->te_buff[k] = get_color_3(mlx, j, i);
			j++;
			k++;
		}
		i++;
	}
}

void    read_south_texture(t_data *mlx)
{
    int i;
	int k;
    int w;
    int h;
    int j;
    
	i = 0;
	k = 0;
    
	mlx->ts_img = mlx_xpm_file_to_image(mlx->mlx, "./textures/bluestone.xpm", &w, &h);
	mlx->ts_addr = mlx_get_data_addr(mlx->ts_img, &mlx->ts_bits_per_pixel, &mlx->ts_line_length, &mlx->ts_endian);
	while (i < 64)
	{
		j = 0;
		while (j < 64)
		{
			mlx->ts_buff[k] = get_color_4(mlx, j, i);
			j++;
			k++;
		}
		i++;
	}
}

void    read_door_texture(t_data *mlx)
{
    int i;
	int k;
    int w;
    int h;
    int j;
    
	i = 0;
	k = 0;

	mlx->door_img = mlx_xpm_file_to_image(mlx->mlx, "./textures/door.xpm", &w, &h);
	mlx->door_addr = mlx_get_data_addr(mlx->door_img, &mlx->door_bits_per_pixel, &mlx->door_line_length, &mlx->door_endian);
	while (i < 64)
	{
	    j = 0;
		while (j < 64)
		{
			mlx->door_buff[k] = get_color_5(mlx, j, i);
			j++;
			k++;
		}
		i++;
	}

}