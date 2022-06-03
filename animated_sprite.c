/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animated_sprite.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:55:22 by aqadil            #+#    #+#             */
/*   Updated: 2022/06/03 21:28:19 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    init_sprite(t_data *mlx)
{
    mlx->sprt_img = mlx_new_image(mlx->mlx, 500, 500);
    mlx->sprt_addr = mlx_get_data_addr(mlx->sprt_img, &mlx->sprt_bits_per_pixel, &mlx->sprt_line_length, &mlx->sprt_endian);
}

void	drawSprite(t_data *mlx)
{

	// if (mlx->px < mlx->spx + 30 && mlx->px > mlx->spx - 30 &&mlx-> py < mlx->spy + 30 && mlx->py > mlx->spy - 30)
	// 	mlx->eat = 1;
	// if (mlx->spx > mlx->px) {mlx->spx = mlx->spx - 0.3;}
	// if (mlx->spx < mlx->px) {mlx->spx = mlx->spx + 0.3;}
	// if (mlx->spy > mlx->py) {mlx->spy = mlx->spy - 0.3;}
	// if (mlx->spy < mlx->py) {mlx->spy = mlx->spy + 0.3;}

	float	sx = mlx->spx - mlx->px;
	float	sy = mlx->spy - mlx->py;
	float	sz = mlx->spz;

	float	CS = cos(degToRad(mlx->pa)), SN = sin(degToRad(mlx->pa));
	float a = sy * CS + sx * SN;
	float b = sx * CS - sy * SN;
	sx = a; sy = b;

	sx = (sx * 108.0 / sy) + (120 / 2);
	sy = (sz * 108.0 / sy) + (80 / 2);
	int i = -1;
	int all = 120 * 80 / b;
    // printf("%f | %f\n", sx, sy);
    // fflush(stdout);
	// sprite attack
    if ( all > 0)
    {
        while (++i < 50)
        {
            int j = -1;
            while (++j < 50)
                mlx_pixel_put(mlx->mlx, mlx->win, sx * 8 - j, sy * 8 - i, 0x00FF0000);
        }
    }
    my_mlx_pixel_put(mlx, (int)(sx / 64), (int)(sy / 64), 0);
    // if (sx > 0 && sx < 120 && b < mlx->depth[(int)sx])
    //     mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->sprt_img, sx * 8, sy * 8);
}
