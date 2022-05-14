/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:36:48 by aqadil            #+#    #+#             */
/*   Updated: 2022/05/13 17:34:11 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// my raycaster calculation and vars
#define PI 3.1415926535
float px, py, pdx, pdy, pa;
int mapS = 64, mapY = 15, mapX = 11;

// pikuma calculation and vars
const int TILE_SIZE = 64;
const int MAP_NUM_ROWS = 11;
const int MAP_NUM_COLS = 15;

//ends here

int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

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
    while (i < MAP_NUM_ROWS)
    {
        j = 0;
        saveI = 0;
        saveJ += loopJ;
        loopI = 0;
        loopJ = 0;
        while (j < MAP_NUM_COLS)
        {
            saveI += loopI;
            loopI = 0;
            loopJ = 0;
            if (map[i][j] == 0)
            {
                while (loopI < TILE_SIZE)
                {
                    loopJ = 0;
                    while (loopJ < TILE_SIZE)
                    {
                        my_mlx_pixel_put(mlx, saveI +loopI, saveJ + loopJ, 0x00FFFFFF); // 0x00FF0000 red
                        loopJ++;
                    }
                    loopI++;
                }
                // had loop 3la 9bel dak line between squares
                while (loopI < TILE_SIZE + 1)
                {
                    loopJ = 0;
                    while (loopJ < TILE_SIZE + 1)
                    {
                        my_mlx_pixel_put(mlx, saveI +loopI, saveJ + loopJ, 0x00000000);
                        loopJ++;
                    }
                    loopI++;
                }
            }
            else if (map[i][j] == 1)
            {
                while (loopI < TILE_SIZE)
                {
                    loopJ = 0;
                    while (loopJ < TILE_SIZE)
                    {
                        my_mlx_pixel_put(mlx, saveI + loopI, saveJ + loopJ, 0x00a9a9a9 );
                        loopJ++;
                    }
                    loopI++;
                }
                while (loopI < TILE_SIZE + 1)
                {
                    loopJ = 0;
                    while (loopJ < TILE_SIZE + 1)
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

// cast rays

void    cast_ray(t_data *mlx)
{
      
}

// end

int	close_it(int keycode, t_data *mlx)
{
    int x = px;
    int y = py;
    
    mlx_clear_window(mlx->mlx, mlx->win);
    if (keycode == left_arrow)
    {
        mlx->player->turnDirection = -1;
        pa -= 0.1 ; if(px < 0){pa += 2 * PI;} pdx = cos(pa) * 5; pdy = sin(pa) * 5;
    }
    if (keycode == right_arrow)
    {
        mlx->player->turnDirection = 1;
        pa += 0.1 ; if(px > 2 * PI){pa -= 2 * PI;} pdx = cos(pa) * 5; pdy = sin(pa) * 5;
    }
    if (keycode == top_arrow)
    {
        mlx->player->walkDirection = 1;
        x = (((x + 10) + pdx) / 64);
        y = (y + pdy)/ 64;
        if (map[y][x] == 0)
            px += pdx; py+= pdy;
    }
    if (keycode == bottom_arrow)
    {
        mlx->player->walkDirection = -1;
        x = (((x) - pdx) / 64);
        y = (y - pdy) / 64;
        if (map[y][x] == 0)
            px -= pdx; py-= pdy;
    }

    // render images
    
    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 1, 1);
    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->player->img, px, py);
    mlx->player->rotationAngle += mlx->player->turnDirection * mlx->player->rotationSpeed;
    float newLineX =   px + pdx * 30;
    float newLineY = py + pdy * 30;
    draw_line((px + 10), py, newLineX + 10, newLineY, mlx);
    
    // just printing player infos and walls 
    
    if (map[y][x] == 1)
    {
        char *map_value = ft_itoa(map[y][x]);
        mlx_string_put(mlx->mlx, mlx->win, 1700, 1, 0x00ffffff, "WALL:");
        mlx_string_put(mlx->mlx, mlx->win, 1780, 1, 0x00ffffff, map_value);
    }
    else
        mlx_string_put(mlx->mlx, mlx->win, 1700, 1, 0x00ffffff, "No Wall");

    char *map_x = ft_itoa(x);
    char *map_y = ft_itoa(y);
    mlx_string_put(mlx->mlx, mlx->win, 1870, 1, 0x00ffffff, "X: ");
    mlx_string_put(mlx->mlx, mlx->win, 1890, 1, 0x00ffffff, map_y);
    mlx_string_put(mlx->mlx, mlx->win, 1910, 1, 0x00ffffff, "Y: ");
    mlx_string_put(mlx->mlx, mlx->win, 1930, 1, 0x00ffffff, map_x);
    char *str_px = ft_itoa(px);
    char *str_py = ft_itoa(py);
    mlx_string_put(mlx->mlx, mlx->win, 1800, 50, 0x00ffffff, "px: ");
    mlx_string_put(mlx->mlx, mlx->win, 1850, 50, 0x00ffffff, str_px);
    mlx_string_put(mlx->mlx, mlx->win, 1800, 80, 0x00ffffff, "py: ");
    mlx_string_put(mlx->mlx, mlx->win, 1850, 80, 0x00ffffff, str_py);

    // pdx and pdy;
    char *str_pdx = ft_itoa(pdx);
    char *str_pdy = ft_itoa(pdy);
    mlx_string_put(mlx->mlx, mlx->win, 1800, 120, 0x00ffffff, "px: ");
    mlx_string_put(mlx->mlx, mlx->win, 1850, 120, 0x00ffffff, str_pdx);
    mlx_string_put(mlx->mlx, mlx->win, 1800, 160, 0x00ffffff, "py: ");
    mlx_string_put(mlx->mlx, mlx->win, 1850, 160, 0x00ffffff, str_pdx);
    
    // player direction;
    char *turn = ft_itoa(mlx->player->turnDirection);
    char *walk = ft_itoa(mlx->player->walkDirection);
    mlx_string_put(mlx->mlx, mlx->win, 1500, 120, 0x00ffffff, "turnDirection: ");
    mlx_string_put(mlx->mlx, mlx->win, 1650, 120, 0x00ffffff, turn);
    mlx_string_put(mlx->mlx, mlx->win, 1500, 160, 0x00ffffff, "walkDirection: ");
    mlx_string_put(mlx->mlx, mlx->win, 1650, 160, 0x00ffffff, walk);
    
    // ray x and y

    char *ray_x = ft_itoa(px + 10);
    char *ray_y = ft_itoa(py);
    char *new_ray_x = ft_itoa(newLineX);
    char *new_ray_y = ft_itoa(newLineY);
    mlx_string_put(mlx->mlx, mlx->win, 1500, 300, 0x00ffffff, "ray_x: ");
    mlx_string_put(mlx->mlx, mlx->win, 1650, 300, 0x00ffffff, ray_x);
    mlx_string_put(mlx->mlx, mlx->win, 1500, 360, 0x00ffffff, "ray_y: ");
    mlx_string_put(mlx->mlx, mlx->win, 1650, 360, 0x00ffffff, ray_y);
    
    mlx_string_put(mlx->mlx, mlx->win, 1500, 400, 0x00ffffff, "new_ray_x: ");
    mlx_string_put(mlx->mlx, mlx->win, 1650, 400, 0x00ffffff, new_ray_x);
    mlx_string_put(mlx->mlx, mlx->win, 1500, 460, 0x00ffffff, "new_ray_y: ");
    mlx_string_put(mlx->mlx, mlx->win, 1650, 460, 0x00ffffff, new_ray_y);

    // angle
    char *angle = ft_itoa(mlx->player->rotationAngle);
    mlx_string_put(mlx->mlx, mlx->win, 1500, 560, 0x00ffffff, "Angle: ");
    mlx_string_put(mlx->mlx, mlx->win, 1650, 560, 0x00ffffff, angle);
    
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

void    playerInit(t_player *player)
{
    player->turnDirection = 0;
    player->walkDirection = 0;
    player->rotationAngle = PI / 2;
    player->moveSpeed = 3.0;
    player->rotationSpeed = 3 * (PI / 180);
}

int main(void)
{
    t_data  mlx;
    t_ray   ray;
    t_player  player;
    
    playerInit(&player);
    pdx = cos(pa) * 5; pdy = sin(pa) * 5;
    mlx.mlx = mlx_init();
    mlx.win_x = 2000;
    mlx.win_y = 1000;
    mlx.win = mlx_new_window(mlx.mlx, 2000, 1000, "Cub3d");
    ray.mlx = mlx.mlx;
    ray.win = mlx.win;
    mlx.ray = &ray;
    player.mlx = mlx.mlx;
    player.win = mlx.win;

    mlx.player = &player;
    
    draw_everything(&mlx, &player, &ray);
    // draw_line2(1, 1, 300, 400 , &mlx);

    
    mlx_hook(mlx.win, 2, 1L<<0, close_it, &mlx);
    mlx_loop(mlx.mlx);
    return (0);
}
