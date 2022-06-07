/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:25:13 by aqadil            #+#    #+#             */
/*   Updated: 2022/06/07 18:10:14 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put2(t_player *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length
			+ x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length
			+ x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	my_mlx_pixel_put_cast(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->cast_addr + (y * data->cast_line_length
			+ x * (data->cast_bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	my_mlx_pixel_put_player(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->player_addr + (y * data->player_line_length
			+ x * (data->player_bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	my_mlx_pixel_put_loading(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->LOADING_addr + (y * data->LOADING_line_length
			+ x * (data->LOADING_bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
