/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animated_sprite.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:55:22 by aqadil            #+#    #+#             */
/*   Updated: 2022/06/10 09:23:39 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    render_animation(t_data *mlx)
{
    mlx_clear_window(mlx->mlx, mlx->win);
    if (mlx->start == 1000)
        mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->sprt.img[0], 500, 500);
    if (mlx->start == 2000)
        mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->sprt.img[1], 500, 500);
    if (mlx->start == 3000)
        mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->sprt.img[2], 500, 500);
    if (mlx->start == 4000)
        mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->sprt.img[3], 500, 500);
    if (mlx->start == 5000)
        mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->sprt.img[4], 500, 500);
    if (mlx->start == 6000)
        mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->sprt.img[5], 500, 500);
    if(mlx->start > 6000)
        mlx->start = 0;
    
}

void    init_sprite_images(t_data *mlx)
{
    mlx->sprt.img[0] = mlx_xpm_file_to_image(mlx->mlx, "./textures//fire/fire-0.xpm", &mlx->sprt.w[0], &mlx->sprt.h[0]);
    mlx->sprt.img[1] = mlx_xpm_file_to_image(mlx->mlx, "./textures//fire/fire-1.xpm", &mlx->sprt.w[1], &mlx->sprt.h[1]);
    mlx->sprt.img[2] = mlx_xpm_file_to_image(mlx->mlx, "./textures//fire/fire-2.xpm", &mlx->sprt.w[2], &mlx->sprt.h[2]);
    mlx->sprt.img[3] = mlx_xpm_file_to_image(mlx->mlx, "./textures//fire/fire-3.xpm", &mlx->sprt.w[3], &mlx->sprt.h[3]);
    mlx->sprt.img[4] = mlx_xpm_file_to_image(mlx->mlx, "./textures//fire/fire-4.xpm", &mlx->sprt.w[4], &mlx->sprt.h[4]);
    mlx->sprt.img[5] = mlx_xpm_file_to_image(mlx->mlx, "./textures//fire/fire-5.xpm", &mlx->sprt.w[5], &mlx->sprt.h[5]);
    mlx->sprt.img[7] = mlx_xpm_file_to_image(mlx->mlx, "./textures/biggun.xpm", &mlx->sprt.w[7], &mlx->sprt.h[7]);
    mlx->sprt.img[8] = mlx_xpm_file_to_image(mlx->mlx, "./textures/gunend.xpm", &mlx->sprt.w[7], &mlx->sprt.h[8]);
    mlx->sprt.x_pos = mlx->win_x / 10;
    mlx->sprt.y_pos = mlx->win_y - 400;
}

void	drawSprite(t_data *mlx)
{
	
}

// 5 8

void    draw_sprt(t_data *mlx, t_vars *var)
{
   
}
