/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:25:13 by aqadil            #+#    #+#             */
/*   Updated: 2022/05/29 16:21:25 by aqadil           ###   ########.fr       */
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

void	my_mlx_pixel_put_cast(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->cast_addr + (y * data->cast_line_length + x * (data->cast_bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	my_mlx_pixel_put_player(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->player_addr + (y * data->player_line_length + x * (data->player_bits_per_pixel / 8));
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

float degToRad(float a)
{ 
	return a*M_PI/180.0;
}

float FixAng(float a)
{ 
	if(a>359)
		a-=360;
	if(a<0)
		a+=360;
	return (a);
}
