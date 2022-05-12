/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:36:48 by aqadil            #+#    #+#             */
/*   Updated: 2022/05/12 15:53:50 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// raycaster vars
#define PI 3.1415926535
float px, py, pdx, pdy, pa;
int mapS = 64, mapY = 8, mapX = 10;


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
    mlx->img = mlx_new_image(mlx->mlx, 800, 630);
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
                        my_mlx_pixel_put(mlx, saveI +loopI, saveJ + loopJ, 0x00FFFFFF); // 0x00FF0000 red
                        loopJ++;
                    }
                    loopI++;
                }
                // had loop 3la 9bel dak line between squares
                while (loopI < 65)
                {
                    loopJ = 0;
                    while (loopJ < 65)
                    {
                        my_mlx_pixel_put(mlx, saveI +loopI, saveJ + loopJ, 0x00000000);
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
                        my_mlx_pixel_put(mlx, saveI + loopI, saveJ + loopJ, 0x00a9a9a9 );
                        loopJ++;
                    }
                    loopI++;
                }
                while (loopI < 65)
                {
                    loopJ = 0;
                    while (loopJ < 65)
                    {
                        my_mlx_pixel_put(mlx, saveI +loopI, saveJ + loopJ, 0x00000000);
                        loopJ++;
                    }
                    loopI++;
                }
            }
            j++;
        }
        i++;
    }
}

int	close_it(int keycode, t_data *mlx)
{
    int x = px;
    int y = py;
    
    mlx_clear_window(mlx->mlx, mlx->win);
    if (keycode == left_arrow)
    {
        pa -= 0.1 ; if(px < 0){pa += 2* PI;} pdx = cos(pa) * 5; pdy = sin(pa) * 5;
    }
    if (keycode == right_arrow)
    {
        pa += 0.1 ; if(px > 2 * PI){pa -= 2 * PI;} pdx = cos(pa) * 5; pdy = sin(pa) * 5;
        
    }
    if (keycode == top_arrow)
    {
        x = (x + 15) / 64;
        y = (y + 15 )/ 64;
        px += pdx; py+= pdy;
    }
    if (keycode == bottom_arrow)
    {
        x = (x / 64);
        y = (y / 64);
        px -= pdx; py-= pdy;
    }

    // render images
    
    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 1, 1);
    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->player->img, px, py);
    draw_line((px + 10), py, (px + 10) + pdx * 30, (py - 70), mlx);
    
    // just printing player infos and walls 
    
    if (map[y][x] == 1)
    {
        char *map_value = ft_itoa(map[x][y]);
        mlx_string_put(mlx->mlx, mlx->win, 700, 1, 0x00ffffff, "WALL:");
        mlx_string_put(mlx->mlx, mlx->win, 780, 1, 0x00ffffff, map_value);
    }
    else
        mlx_string_put(mlx->mlx, mlx->win, 700, 1, 0x00ffffff, "No Wall");

    char *map_x = ft_itoa(x);
    char *map_y = ft_itoa(y);
    mlx_string_put(mlx->mlx, mlx->win, 870, 1, 0x00ffffff, "X: ");
    mlx_string_put(mlx->mlx, mlx->win, 890, 1, 0x00ffffff, map_y);
    mlx_string_put(mlx->mlx, mlx->win, 910, 1, 0x00ffffff, "Y: ");
    mlx_string_put(mlx->mlx, mlx->win, 930, 1, 0x00ffffff, map_x);
    char *str_px = ft_itoa(px);
    char *str_py = ft_itoa(py);
    mlx_string_put(mlx->mlx, mlx->win, 800, 50, 0x00ffffff, "px: ");
    mlx_string_put(mlx->mlx, mlx->win, 850, 50, 0x00ffffff, str_px);
    mlx_string_put(mlx->mlx, mlx->win, 800, 80, 0x00ffffff, "py: ");
    mlx_string_put(mlx->mlx, mlx->win, 850, 80, 0x00ffffff, str_py);

    // pdx and pdy;
    char *str_pdx = ft_itoa(pdx);
    char *str_pdy = ft_itoa(pdy);
    mlx_string_put(mlx->mlx, mlx->win, 800, 120, 0x00ffffff, "px: ");
    mlx_string_put(mlx->mlx, mlx->win, 850, 120, 0x00ffffff, str_pdx);
    mlx_string_put(mlx->mlx, mlx->win, 800, 160, 0x00ffffff, "py: ");
    mlx_string_put(mlx->mlx, mlx->win, 850, 160, 0x00ffffff, str_pdx);
    
	return (0);
}

void    draw_everything(t_data *mlx, t_player *player, t_ray *ray)
{
    drawMap2D(mlx);
    draw_player(player);
    px = player->x;
    py = player->y;
    
    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 1, 1);
    mlx_put_image_to_window(mlx->mlx, mlx->win, player->img, player->x, player->y);
    draw_line(px + 10, py, px + 10, py - 70, mlx);
}

int main(void)
{
    t_data  mlx;
    pdx = cos(pa) * 5; pdy = sin(pa) * 5;
    mlx.mlx = mlx_init();
    mlx.win_x = 1000;
    mlx.win_y = 600;
    mlx.win = mlx_new_window(mlx.mlx, 1000, 600, "Cub3d");
    t_ray   ray;
    ray.mlx = mlx.mlx;
    ray.win = mlx.win;
    t_player  player;
    mlx.ray = &ray;
    player.mlx = mlx.mlx;
    player.win = mlx.win;

    mlx.player = &player;
    
    draw_everything(&mlx, &player, &ray);
    mlx_hook(mlx.win, 2, 1L<<0, close_it, &mlx);
    mlx_loop(mlx.mlx);
    return (0);
}
