/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_into_file_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isegura- <isegura-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 15:43:39 by isegura-          #+#    #+#             */
/*   Updated: 2025/08/26 20:38:48 by isegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	set_player(t_data *data, int x, int y)
{
	data->player.x = x * WALL + WALL / 2;
	data->player.y = y * WALL + WALL / 2;
	data->player.angle = dir_angle(data->map[y][x]);
	data->map[y][x] = '0';
}

int	find_player_position(t_data *data)
{
	int			y;
	int			x;
	static int	player;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (ft_strchr("NSEW", data->map[y][x]))
			{
				player++;
				if (player > 1)
					return (ft_error("Player has several positions"), 1);
				set_player(data, x, y);
			}
			x++;
		}
		y++;
	}
	if (!player)
		return (ft_error("Player position not found"), 1);
	return (0);
}

int	is_map_line(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ' && line[i] != '\n'
			&& line[i] != '\r')
			return (2);
		i++;
	}
	return (1);
}
