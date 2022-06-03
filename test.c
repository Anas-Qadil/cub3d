

#include <stdio.h>
#include <mlx.h>



int main(void)
{
    void *mlx = mlx_init();

    void	*t_img;
	void	*t_addr;
	int		t_bits_per_pixel;
	int		t_line_length;
	int		t_endian;
	int		t_w;
	int		t_h;
	int		colors[32][32];
	int		buff[1500000];

    t_img = mlx_xpm_file_to_image(mlx, "./textures/SO.xpm", &t_w, &t_h);
	t_addr = mlx_get_data_addr(t_img, &t_bits_per_pixel, &t_line_length, &t_endian);
    void    *win = mlx_new_window(mlx, t_w, t_h, "testing");
    int i = 0;
    int k = 0;

	while (i < t_h)
	{
		int j = 0;
		while (j < t_w)
		{
            char	*ptr;
            int		pixel;

            pixel = i * t_line_length + j * 4;
            ptr = t_addr + pixel;
            
			buff[k] = ((((unsigned char)ptr[2]) << 16) + (((unsigned char)ptr[1]) << 8) + ((unsigned char)ptr[0]));
			mlx_pixel_put(mlx, win, j, i, buff[k]);
			j++;
			k++;
		}
		i++;
	}
    mlx_put_image_to_window(mlx, win, t_img, 0, 0);

    mlx_loop(mlx);
}