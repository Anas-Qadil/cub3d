/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:36:48 by aqadil            #+#    #+#             */
/*   Updated: 2022/05/09 19:07:56 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// raycaster vars
#define PI 3.1415926535
float px, py, pdx, pdy, pa;

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

//end here

// draw func

void	draw(t_point a, t_point b, t_data *param)
{
	float	dx;
	float	dy;
	float	max;

	dx = b.x - a.x;
	dy = b.y - a.y;
	max = ft_abs(fmodule(dx), fmodule(dy));
	dx = dx / max;
	dy = dy / max;
	while ((int)(a.x - b.x) || (int)(a.y - b.y))
	{
		mlx_pixel_put(param->mlx, param->win, a.x, a.y, 0x00009CFF);
		a.x = a.x + dx;
		a.y = a.y + dy;
		if (a.x > 2000 || a.y > 1000 || a.y < 0 || a.x < 0)
			break ;
	}
}

//end

void    draw_player(t_player *mlx)
{
    int i = 0;
    int j = 0;

    mlx->img = mlx_new_image(mlx->mlx, 30, 30);

    mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length,
								&mlx->endian);
    mlx->x = 500;
    mlx->y = 500;
    while (i < 20)
    {
        j = 0;
        while (j < 10)
        {
            my_mlx_pixel_put2(mlx, i, j, 0x00009CFF);
            j++;
        }
        i++;
    }
    i = 5;
    j = 0;
    // while (i < 10)
    // {
    //     j = 0;
        while (j < 20)
        {
            my_mlx_pixel_put2(mlx, px++, py++, 0x00009CFF);
            j++;
        }
    //     i++;
    // }
    // mlx_hook(mlx->win, 2, 1L<<0, close_it, mlx);
    // mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, mlx->x, mlx->y);
    // return (mlx);
}


void	ft_putchar(char c) {
	write(1, &c, 1);
}

void	ft_putnbr(int nb) {
	if (nb < 0) {
		ft_putchar('-');
		nb = -nb;
	}
	if (nb >= 10) {
		ft_putnbr(nb / 10);
		nb = nb % 10;
	}
	if (nb < 10) ft_putchar(nb + 48);
}

int mapS = 64, mapY = 8, mapX = 10;

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

int map[8][11] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

int	key_hook(int keycode, t_data *cube)
{
	if (keycode == left_arrow)
    {
        printf("left arrow has been pressed : %d\n", cube->x);
        cube->x += 100;
    }
	return (0);
}


void    drawMap2D(t_data *mlx)
{
    int i = 0, j = 0;
    int loopI = 0, loopJ = 0;
    int saveI, saveJ;
    mlx->img = mlx_new_image(mlx->mlx, 2000, 1000);
    mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length,
								&mlx->endian);

    mlx->x = 1;
    mlx->y = 1;
    while (i < mapY)
    {
        j = 0;
        saveI = 0;
        saveJ += loopJ;
        
            loopI = 0;
            loopJ = 0;
        while (j < mapX)
        {
            saveI += loopI;
            loopI = 0;
            loopJ = 0;
            if (map[i][j] == 0)
            {
                while (loopI < 64)
                {
                    loopJ = 0;
                    while (loopJ < 64)
                    {
                        my_mlx_pixel_put(mlx, saveI +loopI - 3, saveJ + loopJ + 3, 0x00FF0000);
                        loopJ++;
                    }
                    loopI++;
                }
            }
            else if (map[i][j] == 1)
            {
                while (loopI < 64)
                {
                    loopJ = 0;
                    while (loopJ < 64)
                    {
                        my_mlx_pixel_put(mlx, saveI + loopI + 3, saveJ + loopJ - 3, 0x00FFFFFF);
                        loopJ++;
                    }
                    loopI++;
                }
            }
            j++;
        }
        i++;
    }
    // draw_player(mlx);
    // mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 1, 1);
}

int	close_it(int keycode, t_data *mlx)
{
    mlx_clear_window(mlx->mlx, mlx->win);
    if (keycode == left_arrow)
    {
        pa -= 0.1 ; if(px < 0){pa += 2* PI;} pdx = cos(pa) * 5; pdy = sin(pa) * 5;
        mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 1, 1); // map
        
        mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->player->img, px, py); //player
        
    }
    if (keycode == right_arrow)
    {
        pa += 0.1 ; if(px > 2 * PI){pa -= 2 * PI;} pdx = cos(pa) * 5; pdy = sin(pa) * 5;
        
        mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 1, 1); // map
        mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->player->img, px, py);
    }
    if (keycode == top_arrow)
    {
        px += pdx; py+= pdy;
        mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 1, 1); // map
        mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->player->img, px, py);
    }
    if (keycode == bottom_arrow)
    {
        px -= pdx; py-= pdy;
        mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 1, 1); // map
        mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->player->img, px, py);
    }
	return (0);
}

void    draw_everything(t_data *mlx, t_player *player)
{
    drawMap2D(mlx);
    draw_player(player);
    
    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 1, 1);
    mlx_put_image_to_window(mlx->mlx, mlx->win, player->img, 500, 500);
}


void    ray_image(t_data *mlx, t_point a, t_point b)
{
    mlx->ray->img = mlx_new_image(mlx->mlx, 2000, 1000);
    mlx->ray->addr = mlx_get_data_addr(mlx->ray->img, &mlx->ray->bits_per_pixel, &mlx->ray->line_length,
								&mlx->ray->endian);
    float	dx;
	float	dy;
	float	max;

	dx = b.x - a.x;
	dy = b.y - a.y;
	max = ft_abs(fmodule(dx), fmodule(dy));
	dx = dx / max;
	dy = dy / max;
    printf("%f %f %f\n", max, dx, dy);
	while ((int)(a.x - b.x) || (int)(a.y - b.y))
	{
		my_mlx_pixel_put(mlx, a.x, a.y, 0x00009CFF);
		a.x = a.x + dx;
		a.y = a.y + dy;
		if (a.x > 2000 || a.y > 1000 || a.y < 0 || a.x < 0)
			break ;
	}
    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->ray->img, 1, 1);
}

int main(void)
{
    t_data  mlx;
    pdx = cos(pa) * 5; pdy = sin(pa) * 5;
    mlx.mlx = mlx_init();
    mlx.win = mlx_new_window(mlx.mlx, 2000, 1000, "Cub3d");
    t_ray   ray;
    t_player  player;
    mlx.ray = &ray;
    player.mlx = mlx.mlx;
    player.win = mlx.win;

    mlx.player = &player;
    
    t_point a, b;
    a.x = 1.12;
    a.y = 1.12;
    b.x = 1900.1;
    b.y = 900.2;
    draw_everything(&mlx, &player);
    // ray_image(&mlx, a, b);
    // draw(a, b, &mlx);
    // drawMap2D(&mlx);
    // draw_player(&player);

    
    mlx_hook(mlx.win, 2, 1L<<0, close_it, &mlx);
    

    mlx_loop(mlx.mlx);
    return (0);
}