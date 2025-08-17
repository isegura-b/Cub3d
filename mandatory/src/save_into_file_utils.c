#include "../inc/cub.h"

float	dir_angle(char c)
{
	if (c == 'N')
		return (3 * PI / 2);
	if (c == 'S')
		return (PI / 2);
	if (c == 'E')
		return (0);
	return (PI);
}

int	find_player_position(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (ft_strchr("NSEW", data->map[y][x]))
			{
				data->player.x = x * WALL + WALL / 2;
				data->player.y = y * WALL + WALL / 2;
				data->player.angle = dir_angle(data->map[y][x]);
				data->map[y][x] = '0';
				return (0);
			}
			x++;
		}
		y++;
	}
	return (ft_error("Player position not found"), 1);
}
