/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 14:16:13 by aqadil            #+#    #+#             */
/*   Updated: 2022/06/03 10:51:03 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init(t_data *mlx)
{
	read_textures(mlx);
	create_images(mlx);
}

void	init_vars(t_data *mlx)
{
	mlx->type = 1;
	mlx->state = 1;
	mlx->map = 0;
	mlx->spx = 8 * 64;
	mlx->spy = 4 * 64;
	mlx->spz= 20;
}

void	drawMap2D_init(t_map_vars *var)
{
	var->i = -1;
	var->j = -1;
	var->loopI = 0;
	var->loopJ = 0;
	var->saveI = 0;
	var->saveJ = 0;
}

void   init_hooks(t_data *mlx)
{
	mlx->move_up = 0;
	mlx->move_down = 0;
	mlx->move_right = 0;
	mlx->move_left = 0;
}

void	init_cast_vars(t_vars *var, t_data *mlx)
{
	float calul = (float)(mlx->win_x / 1000.0);
	
	var->rays_num =  mlx->win_x;
	var->next_ra = (0.060 / ((calul) + ((calul * 5) / 100)));
	var->color = 0x00e83838;
	var->max_ray_checks = 20;
	var->r = 0;
	var->ra = FixAng(mlx->pa+30);
	var->i = 0;
	var->hx = mlx->px;
	var->hy = mlx->py;
}

void	init_window(t_data *mlx)
{
	mlx->win_x = 1500;
	mlx->win_y = 1000;
	
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, mlx->win_x, mlx->win_y, "Cub3d");
}

void	init_map(t_data *mlx)
{
	mlx->square_size = 16;
	mlx->mapS = 64;
	mlx->mapY = 11;
	mlx->mapX = 15;
	mlx->line_height = mlx->win_y / 2;
}

void	init_player(t_data *mlx)
{
	mlx->pa = 90;
	mlx->px = get_player_x_pos(mlx);
	mlx->py = get_player_y_pos(mlx);
	mlx->pdx = cos(degToRad(mlx->pa));
	mlx->pdy = -sin(degToRad(mlx->pa));
}

void	draw_Loading(t_data *mlx)
{
	int i = 0;
	int j = 0;

	while (mlx->LOADING_i < 1)
	{
		while (mlx->LOADING_j < mlx->LOADING_w)
		{
			my_mlx_pixel_put_Loading(mlx, mlx->LOADING_j, mlx->LOADING_i, 0x00FFFFFF);
			mlx->LOADING_j++;
			if (mlx->LOADING_j % 2 == 0)
			{
				break;
			}
		}
		if (mlx->LOADING_j >= mlx->LOADING_w - 1)
		{
			mlx->LOADING_i++;
			mlx->isLoadingDone = 1;
		}
		if (mlx->LOADING_j % 2 == 0)
			break;
	}
}

void	read_HOME_image(t_data *mlx)
{
	int w, h;
	mlx->HOME_img = mlx_xpm_file_to_image(mlx->mlx, "./textures/CUB3d.xpm", &w, &h);
	mlx->HOME_addr = mlx_get_data_addr(mlx->HOME_img, &mlx->bits_per_pixel, &mlx->HOME_line_length, &mlx->HOME_endian);
	mlx->HOME_w = w;
	mlx->HOME_h = h;

	mlx->PRESS_img = mlx_xpm_file_to_image(mlx->mlx, "./textures/Press.xpm", &w, &h);
	mlx->PRESS_addr = mlx_get_data_addr(mlx->PRESS_img, &mlx->bits_per_pixel, &mlx->PRESS_line_length, &mlx->PRESS_endian);
	mlx->PRESS_w = w;
	mlx->PRESS_h = h;
	
	
	
	mlx->LOADING_img = mlx_new_image(mlx->mlx, mlx->LOADING_w, mlx->LOADING_h);
	mlx->LOADING_addr = mlx_get_data_addr(mlx->LOADING_img, &mlx->LOADING_bits_per_pixel, &mlx->LOADING_line_length, &mlx->LOADING_endian);
	
}

void	init_home_screen_vars(t_data *mlx)
{
	mlx->LOADING_i = 0;
	mlx->LOADING_j = 0;
	mlx->LOADING_counter = 0;
	mlx->isLoadingDone = 0;
	mlx->LOADING_w = 300;
	mlx->LOADING_h = 50;
}

void	init_everything(t_data *mlx)
{
	mlx->gameState = HOME_SCREEN;
	init_window(mlx);
	init_map(mlx);
	init_player(mlx);
	init_hooks(mlx);
	init_vars(mlx);
	init(mlx);
	init_home_screen_vars(mlx);
	read_HOME_image(mlx);
}
