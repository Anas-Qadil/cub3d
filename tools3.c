/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:47:19 by aqadil            #+#    #+#             */
/*   Updated: 2022/06/11 18:47:40 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_win(void)
{
	exit(0);
}

void	mouse_helper(int x, int y, t_data *mlx)
{
	if (x > mlx->mouse_x + 20)
	{
		mlx->move_right = 1;
		mlx->move_left = 0;
		mlx->mouse_x = x;
	}
	else
		mlx->move_right = 0;
	if (x < mlx->mouse_x - 20)
	{
		mlx->move_left = 1;
		mlx->move_right = 0;
		mlx->mouse_x = x;
	}
	else
		mlx->move_left = 0;
}
