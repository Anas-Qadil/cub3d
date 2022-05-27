/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:24:19 by aqadil            #+#    #+#             */
/*   Updated: 2022/05/25 14:34:17 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    draw_player(t_player *mlx)
{
    int i = 0;
    int j = 0;

    mlx->img = mlx_new_image(mlx->mlx, 5, 5);

    mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length,
								&mlx->endian);
    mlx->x = 150;
    mlx->y = 600;
    while (i < 5)
    {
        j = 0;
        while (j < 5)
        {
            my_mlx_pixel_put2(mlx, i, j, 0x00FF0000);
            j++;
        }
        i++;
    }
}

void draw_line(float ax, float ay, float bx, float by, t_data *param, int color)
{
	float	dx;
	float	dy;
	float	max;
    

	dx = bx - ax;
	dy = by - ay;
	max = ft_abs(fmodule(dx), fmodule(dy));
	dx = dx / max;
	dy = dy / max;
	while ((int)(ax - bx) || (int)(ay - by))
	{
		mlx_pixel_put(param->mlx, param->win, ax, ay, color);
		ax = ax + dx;
		ay = ay + dy;
		if (ax > param->win_x || ay > param->win_y || ay < 0 || ax < 0)
			break ;
	}
}

void draw_line_wall(float ax, float ay, float bx, float by, t_data *param, int color)
{
	float	dx;
	float	dy;
	float	max;
    int i = 0;
    

	dx = bx - ax;
	dy = by - ay;
	max = ft_abs(fmodule(dx), fmodule(dy));
	dx = dx / max;
	dy = dy / max;
	while ((int)(ax - bx) || (int)(ay - by))
	{
		my_mlx_pixel_put(param, ax, ay, color);
		ax = ax + dx;
		ay = ay + dy;
        i++;
		if (ax > param->win_x || ay > param->win_y || ay < 0 || ax < 0)
			break ;
	}
}
