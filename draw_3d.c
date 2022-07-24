/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:12:37 by aqadil            #+#    #+#             */
/*   Updated: 2022/07/24 08:59:46 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	painting_the_line(t_vars *var, t_data *mlx)
{
	while (var->y < var->line_h)
	{
		if (var->shade == 1)
			handle_east_west(var, mlx);
		else
			handle_north_south(var, mlx);
		my_mlx_pixel_put_cast(mlx, var->r,
			var->y + var->line_offset, mlx->color);
		var->y++;
		var->ty += (var->ty_step);
	}
}

void	put_sprite_images(t_data *mlx)
{
	if (mlx->animation_dur < 2)
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->sprt.img[0], 0, 520);
	else if (mlx->animation_dur < 4)
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->sprt.img[1], 0, 520);
	else if (mlx->animation_dur < 6)
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->sprt.img[2], 0, 520);
	else if (mlx->animation_dur < 8)
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->sprt.img[3], 0, 520);
	else if (mlx->animation_dur < 10)
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->sprt.img[4], 0, 520);
	else if (mlx->animation_dur < 12)
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->sprt.img[5], 0, 520);
	else if (mlx->animation_dur > 12)
		mlx->animation_dur = 0;
}

void	draw_everything(t_data *mlx)
{
	mlx_clear_window(mlx->mlx, mlx->win);
	draw_player(mlx);
	cast(mlx, 0);
	draw_map_2d(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->cast_img, 0, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->player_img,
		mlx->px / 4, mlx->py / 4);
	if (mlx->gun_state == 0)
		mlx_put_image_to_window(mlx->mlx, mlx->win,
			mlx->sprt.img[7], mlx->sprt.x_pos, mlx->sprt.y_pos);
	else
	{
		mlx_put_image_to_window(mlx->mlx, mlx->win,
			mlx->sprt.img[8], mlx->sprt.x_pos, mlx->sprt.y_pos - 90);
		if (mlx->gun_start % 20 == 0)
		{
			mlx->gun_state = 0;
			mlx->gun_start = 0;
		}
	}
	put_sprite_images(mlx);
}
