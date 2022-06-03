

#include <stdio.h>
#include <mlx.h>

// void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int*)dst = color;
// }

int main(void)
{
    void *mlx = mlx_init();
    void    *win = mlx_new_window(mlx, 1000, 1000, "testing");

    void	*LOADING_img;
	void	*LOADING_addr;
	int		LOADING_bits_per_pixel;
	int		LOADING_line_length;
	int		LOADING_endian;

    LOADING_img = mlx_new_image(mlx, 50, 50);
	LOADING_addr = mlx_get_data_addr(LOADING_img, &LOADING_bits_per_pixel, &LOADING_line_length, &LOADING_endian);
	// draw_Loading(mlx);

    int x = 1, y = 1;
    char	*dst;

	dst = LOADING_addr + (y * LOADING_line_length + x * (LOADING_bits_per_pixel / 8));
    *(unsigned int*)dst = 0x00FFFFFF;

    mlx_put_image_to_window(mlx, win, LOADING_img, 0, 0);

    mlx_loop(mlx);
}