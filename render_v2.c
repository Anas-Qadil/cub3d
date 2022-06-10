/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_v2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:53:06 by aqadil            #+#    #+#             */
/*   Updated: 2022/06/10 11:25:52 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int map[15][33];

void	update_move_up(t_data *mlx, t_keyvars *var)
{
	if (map[var->ipy_add_yo][var->ipx_add_xo] == 1 &&
		map[var->ipy][var->ipx_add_xo] == 0 &&
		map[var->ipy_add_yo][var->ipx] == 0)
			;
	else
	{
		if (check_valid_move(var, map[var->ipy][var->ipx_add_xo]))
			mlx->px += mlx->pdx * 6 * mlx->move_up;
		if (check_valid_move(var, map[var->ipy_add_yo][var->ipx]))
			mlx->py += mlx->pdy * 6 * mlx->move_up;
	}
	mlx->move_down = 0;
}

void	update_move_down(t_data *mlx, t_keyvars *var)
{
	if (check_valid_move(var, map[var->ipy][var->ipx_sub_xo]))
		mlx->px -= mlx->pdx * 6 * mlx->move_down;
	if (check_valid_move(var, map[var->ipy_sub_yo][var->ipx]))
		mlx->py -= mlx->pdy * 6 * mlx->move_down;
	mlx->move_up = 0;
}

void	update_a_pressed(t_data *mlx, t_keyvars *var)
{
	if (check_valid_move(var, map[var->turn_ipy][var->turn_ipx_add_xo]))
		mlx->px += var->turn_pdx * 4 * mlx->a_pressed;
	if (check_valid_move(var, map[var->turn_ipy_add_yo][var->turn_ipx]))
		mlx->py += var->turn_pdy * 4 * mlx->a_pressed;
}

void	update_d_pressed(t_data *mlx, t_keyvars *var)
{
	if (check_valid_move(var, map[var->turn_ipy][var->turn_ipx_sub_xo]))
		mlx->px -= var->turn_pdx * 4 * mlx->d_pressed;
	if (check_valid_move(var, map[var->turn_ipy_sub_yo][var->turn_ipx]))
		mlx->py -= var->turn_pdy * 4 * mlx->d_pressed;
	mlx->a_pressed = 0;
}
