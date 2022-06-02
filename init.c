/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 14:16:13 by aqadil            #+#    #+#             */
/*   Updated: 2022/06/02 19:28:37 by aqadil           ###   ########.fr       */
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
	// printf("%f\n", calul);
	// printf("%d\n", var->rays_num);
	var->next_ra = (0.060 / ((calul) + ((calul * 5) / 100)));
	// printf("%f\n", var->next_ra);
	// fflush(stdout);
	var->color = 0x00e83838;
	var->max_ray_checks = 20;
	var->r = 0;
	var->ra = FixAng(mlx->pa+30);
	var->i = 0;
	var->hx = mlx->px;
	var->hy = mlx->py;
}

void	init_everything(t_data *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win_x = 1500;
	mlx->win_y = 1000;
	mlx->win = mlx_new_window(mlx->mlx, mlx->win_x, mlx->win_y, "Cub3d");
	mlx->square_size = 16;
	mlx->mapS = 64;
	mlx->mapY = 11;
	mlx->mapX = 15;
	mlx->pa = 90;
	mlx->px = get_player_x_pos(mlx);
	mlx->py = get_player_y_pos(mlx);
	mlx->pdx = cos(degToRad(mlx->pa)); 
	mlx->pdy = -sin(degToRad(mlx->pa));
	mlx->line_height = mlx->win_y / 2;
	
	init_hooks(mlx);
	init_vars(mlx);
	init(mlx);
}

