/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 14:16:13 by aqadil            #+#    #+#             */
/*   Updated: 2022/06/11 19:10:36 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init(t_data *mlx)
{
	read_textures(mlx);
	create_images(mlx);
}

void	init_player(t_data *mlx)
{
	get_player_direction(mlx);
	mlx->px = get_player_x_pos(mlx);
	mlx->py = get_player_y_pos(mlx);
	mlx->pdx = cos(deg_to_rad(mlx->pa));
	mlx->pdy = -sin(deg_to_rad(mlx->pa));
}

void	init_window(t_data *mlx)
{
	mlx->win_x = 1500;
	mlx->win_y = 1000;
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, mlx->win_x,
			mlx->win_y, "Cub3d");
}

void	init_floor_cieling_colors(t_data *mlx)
{
	mlx->floor_color = mlx->world->floor_color_;
	mlx->cieling_color = mlx->world->ceilling_color_;
}

void	init_everything(t_data *mlx)
{
	mlx->game_state = GAME;
	init_floor_cieling_colors(mlx);
	open_textures(mlx);
	init_window(mlx);
	init_map(mlx);
	init_player(mlx);
	init_hooks(mlx);
	init(mlx);
	init_home_screen_vars(mlx);
	read_home_image(mlx);
}
