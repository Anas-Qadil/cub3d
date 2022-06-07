/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animated_sprite.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:55:22 by aqadil            #+#    #+#             */
/*   Updated: 2022/06/07 18:33:14 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	drawSprite(t_data *mlx)
{
	int x = 5 * 64;
    int y = 8 * 64;
    int color = 0;
    while (y < y + 200)
    {
        int x = 5 * 64;
        while (x < x + 200)
        {
            my_mlx_pixel_put_cast(mlx, x, y, color);
            x++;
        }
        y++;
    }
}

// 5 8

void    draw_sprt(t_data *mlx, t_vars *var)
{
    int color = 0x0000FF00;
    int j = 0;
    
    while (var->y < 200)
    {
        my_mlx_pixel_put_cast(mlx, var->r + 20, var->y + var->lineOff, color);
        var->y++;
    }
}
