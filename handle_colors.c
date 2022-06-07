/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 14:14:26 by aqadil            #+#    #+#             */
/*   Updated: 2022/06/07 15:25:21 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	get_color(t_data *mlx, int x, int y)
{
	char	*ptr;
	int		pixel;

	pixel = y * mlx->t_line_length + x * 4;
	ptr = mlx->t_addr + pixel;
	return ((((unsigned char)ptr[2]) << 16)
		+ (((unsigned char)ptr[1]) << 8) + ((unsigned char)ptr[0]));
}

unsigned int	get_color_2(t_data *mlx, int x, int y)
{
	char	*ptr;
	int		pixel;

	pixel = y * mlx->tw_line_length + x * 4;
	ptr = mlx->tw_addr + pixel;
	return ((((unsigned char)ptr[2]) << 16)
		+ (((unsigned char)ptr[1]) << 8) + ((unsigned char)ptr[0]));
}

unsigned int	get_color_3(t_data *mlx, int x, int y)
{
	char	*ptr;
	int		pixel;

	pixel = y * mlx->te_line_length + x * 4;
	ptr = mlx->te_addr + pixel;
	return ((((unsigned char)ptr[2]) << 16)
		+ (((unsigned char)ptr[1]) << 8) + ((unsigned char)ptr[0]));
}

unsigned int	get_color_4(t_data *mlx, int x, int y)
{
	char	*ptr;
	int		pixel;

	pixel = y * mlx->ts_line_length + x * 4;
	ptr = mlx->ts_addr + pixel;
	return ((((unsigned char)ptr[2]) << 16)
		+ (((unsigned char)ptr[1]) << 8) + ((unsigned char)ptr[0]));
}

unsigned int	get_color_5(t_data *mlx, int x, int y)
{
	char	*ptr;
	int		pixel;

	pixel = y * mlx->door_line_length + x * 4;
	ptr = mlx->door_addr + pixel;
	return ((((unsigned char)ptr[2]) << 16)
		+ (((unsigned char)ptr[1]) << 8) + ((unsigned char)ptr[0]));
}
