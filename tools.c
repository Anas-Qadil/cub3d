/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:25:13 by aqadil            #+#    #+#             */
/*   Updated: 2022/05/14 10:07:51 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put3(t_ray *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	my_mlx_pixel_put2(t_player *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

float	fmodule(float i)
{
	if (i < 0)
		return (-i);
	else
		return (i);
}

float	ft_abs(float dx, float dy)
{
	float	max;

	if (dx > dy)
		max = dx;
	else
		max = dy;
	return (max);
}

// void	ft_putchar(char c) {
// 	write(1, &c, 1);
// }

// void	ft_putnbr(int nb) {
// 	if (nb < 0) {
// 		ft_putchar('-');
// 		nb = -nb;
// 	}
// 	if (nb >= 10) {
// 		ft_putnbr(nb / 10);
// 		nb = nb % 10;
// 	}
// 	if (nb < 10) ft_putchar(nb + 48);
// }
