#include "../inc/cub.h"

void	draw_sky(int x, int end_y, t_data *data)
{
	int	y;

	y = 0;
	while (y < end_y)
	{
		my_pixel_put(x, y, data->info_file.sky, data);
		y++;
	}
}

void	draw_floor(int x, int start_y, t_data *data)
{
	int	y;

	y = start_y;
	while (y < HEIGHT)
	{
		my_pixel_put(x, y, data->info_file.floor, data);
		y++;
	}
}


