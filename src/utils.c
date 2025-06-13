#include "../inc/cub.h"

void	ft_error(char *error_str)
{
	printf("Error : %s\n", error_str);
	exit(EXIT_FAILURE);
}

void	my_pixel_put(int x, int y, int color, t_data *img)
{
	int	offset;
    
	if(x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
        return;
	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->info + offset) = color;
}

int	handle_exit(void *param)
{
	t_data *data = (t_data *)param;

	mlx_destroy_window(data->mlx, data->win);
	exit(0);
	return (0);
}