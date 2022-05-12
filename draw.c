/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:24:19 by aqadil            #+#    #+#             */
/*   Updated: 2022/05/12 15:33:44 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    draw_player(t_player *mlx)
{
    int i = 0;
    int j = 0;

    mlx->img = mlx_new_image(mlx->mlx, 20, 20);

    mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length,
								&mlx->endian);
    mlx->x = 300;
    mlx->y = 400;
    while (i < 20)
    {
        j = 0;
        while (j < 20)
        {
            my_mlx_pixel_put2(mlx, i, j, 0x00009CFF);
            j++;
        }
        i++;
    }
}



void	draw_line(int ax, int ay, int bx, int by, t_data *param)
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
		mlx_pixel_put(param->mlx, param->win, ax, ay, 0x00009CFF);
		ax = ax + dx;
		ay = ay + dy;
        i++;
		if (ax > param->win_x || ay > param->win_y || ay < 0 || ax < 0 || ay == by)
			break ;
	}
}

void	draw_ray(int ax, int ay, int bx, int by, t_data *param)
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
		my_mlx_pixel_put(param, ax, ay, 0x00ff0000);
		ax = ax + dx;
		ay = ay + dy;
        i++;
		if (ax > param->win_x || ay > param->win_y || ay < 0 || ax < 0 || ax == bx || ay == by)
			break ;
	}
}