/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 14:12:34 by aqadil            #+#    #+#             */
/*   Updated: 2022/06/11 19:10:41 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_home_screen_vars(t_data *mlx)
{
	mlx->loading_i = 0;
	mlx->loading_j = 0;
	mlx->loading_counter = 0;
	mlx->isloadingdone = 0;
	mlx->loading_w = 300;
	mlx->loading_h = 50;
}
