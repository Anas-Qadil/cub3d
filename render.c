/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 15:10:50 by aqadil            #+#    #+#             */
/*   Updated: 2022/06/07 18:12:14 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int map[11][15];

int	check_valid_move(t_keyvars *var, int pos)
{
	if (pos == NORTH || pos == WEST || pos == SOUTH
		|| pos == EAST || pos == 0 || pos == DOOR_CLOSED)
		return (1);
	return (0);
}

void	update_everything(t_data *mlx)
{
	t_keyvars	var;

	keycode_init(&var, mlx);
	if (mlx->move_left == 1)
	{
		mlx->pa += 0.2 * 10 * mlx->move_left;
		mlx->move_right = 0;
	}
	else if (mlx->move_right == 1)
	{
		mlx->pa -= 0.2 * 10 * mlx->move_right;
		mlx->move_left = 0;
	}
	mlx->pa = fix_ang(mlx->pa);
	mlx->pdx = cos(deg_to_rad(mlx->pa));
	mlx->pdy = -sin(deg_to_rad(mlx->pa));
	if (mlx->move_up == 1)
		update_move_up(mlx, &var);
	if (mlx->move_down == 1)
		update_move_down(mlx, &var);
	if (mlx->a_pressed)
		update_a_pressed(mlx, &var);
	if (mlx->d_pressed)
		update_d_pressed(mlx, &var);
}

void	read_textures(t_data *mlx)
{
	read_north_texture(mlx);
	read_west_texture(mlx);
	read_east_texture(mlx);
	read_south_texture(mlx);
	read_door_texture(mlx);
}

void	check_doors(t_data *mlx)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < mlx->mapY)
	{
		j = 0;
		while (j < mlx->mapX)
		{
			if (map[i][j] == DOOR_CLOSED)
				map[i][j] = DOOR;
			j++;
		}
		i++;
	}
}

int	render(t_data *mlx)
{
	mlx_clear_window(mlx->mlx, mlx->win);
	if (mlx->gameState == GAME)
	{
		update_everything(mlx);
		draw_everything(mlx);
		mlx->start++;
		if (mlx->start == 100)
			check_doors(mlx);
		check_if_player_is_dead(mlx);
	}
	if (mlx->gameState == HOME_SCREEN)
		render_home_screen(mlx);
	if (mlx->gameState == LOSE)
		render_lose_screen(mlx);
	return (1);
}
