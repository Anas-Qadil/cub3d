/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 11:05:42 by aqadil            #+#    #+#             */
/*   Updated: 2022/06/07 15:17:51 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_and_exit(t_data *mlx)
{
	free(mlx->buff);
	free(mlx->ts_buff);
	free(mlx->tw_buff);
	free(mlx->te_buff);
	free(mlx->door_buff);
	exit(0);
}
