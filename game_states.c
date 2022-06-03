/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_states.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:39:17 by aqadil            #+#    #+#             */
/*   Updated: 2022/06/03 15:29:13 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int map[11][15];

void    render_lose_screen(t_data *mlx)
{
    int w, h;
    int x, y;
    mlx->LOSE_img = mlx_xpm_file_to_image(mlx->mlx, "./textures/you-lose.xpm", &w, &h);
    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->LOSE_img, 0, 0);
}

void    check_if_player_is_dead(t_data *mlx)
{
    if (map[(int)(mlx->py / 64)][(int)(mlx->px / 64)] == DOOR)
        mlx->gameState = LOSE;
}

void    render_home_screen(t_data *mlx)
{
    int HOME_x = (mlx->win_x / 2) - (mlx->HOME_w / 2);
	int load_x = (mlx->win_x / 2) - (mlx->LOADING_w / 2);
	int load_y = (mlx->win_y / 2) + (mlx->win_y / 2.8);
    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->HOME_img, HOME_x, 0);
	if (mlx->isLoadingDone == 0)
	{
		if (mlx->LOADING_counter % 2 == 0)
			draw_Loading(mlx);
		mlx->LOADING_counter++;
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->LOADING_img, load_x, load_y);
	}
    else
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->PRESS_img, load_x - 100, load_y - 50);
    // printf("hello\n");
    // fflush(stdout);
}