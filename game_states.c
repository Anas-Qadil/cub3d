/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_states.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:39:17 by aqadil            #+#    #+#             */
/*   Updated: 2022/06/07 20:55:54 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int map[11][15];

void	render_lose_screen(t_data *mlx)
{
	int	h;
	int	w;

	mlx->lose_img = mlx_xpm_file_to_image(mlx->mlx,
			"./textures/you-lose.xpm", &w, &h);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->lose_img, 0, 0);
}

void	check_if_player_is_dead(t_data *mlx)
{
	if (map[(int)(mlx->py / 64)][(int)(mlx->px / 64)] == DOOR)
		mlx->game_state = lose;
}

void	render_home_screen(t_data *mlx)
{
	int	home_x;
	int	load_x;
	int	load_y;

	home_x = (mlx->win_x / 2) - (mlx->home_w / 2);
	load_x = (mlx->win_x / 2) - (mlx->loading_w / 2);
	load_y = (mlx->win_y / 2) + (mlx->win_y / 2.8);
	mlx_put_image_to_window(mlx->mlx, mlx->win,
		mlx->home_img, home_x, 0);
	if (mlx->isloadingdone == 0)
	{
		if (mlx->loading_counter % 2 == 0)
			draw_loading(mlx);
		mlx->loading_counter++;
		mlx_put_image_to_window(mlx->mlx, mlx->win,
			mlx->loading_img, load_x, load_y);
	}
	else
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->press_img,
			load_x - 100, load_y - 50);
}
