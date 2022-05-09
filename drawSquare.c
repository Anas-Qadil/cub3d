/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawSquare.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:04:12 by aqadil            #+#    #+#             */
/*   Updated: 2022/05/08 11:12:38 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    draw_square(t_data *mlx, int x)
{
    int i = 0, j = 0;

    while (i < 5)
    {
        j = 0;
        while (j < 5)
        {
            if (x == 1)
                my_mlx_pixel_put(mlx, i, j, 0x00FFFFFF);
            else
                my_mlx_pixel_put(mlx, i, j, 0x00FF0000);
        }
        i++;
    }
}
