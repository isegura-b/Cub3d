/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isegura- <isegura-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 15:38:51 by isegura-          #+#    #+#             */
/*   Updated: 2025/08/17 16:26:03 by isegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

static int	flood_fill(t_mapinfo *info, int x, int y)
{
	if (x < 0 || y < 0 || x >= info->width || y >= info->height)
		return (0);
	if (info->map[y][x] == '1' || info->map[y][x] == 'F')
		return (1);
	if (info->map[y][x] == ' ')
		return (0);
	if (is_invalid_char(info->map[y][x]))
		return (0);
	info->map[y][x] = 'F';
	if (!flood_fill(info, x + 1, y))
		return (0);
	if (!flood_fill(info, x - 1, y))
		return (0);
	if (!flood_fill(info, x, y + 1))
		return (0);
	if (!flood_fill(info, x, y - 1))
		return (0);
	return (1);
}

int	find_player(char **map, int h, int w, t_point *p)
{
	int	i;
	int	j;

	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
			{
				p->x = j;
				p->y = i;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	is_map_closed(char **map, int h, int w)
{
	t_mapinfo	info;
	char		**tmp;
	t_point		player;

	tmp = copy_map(map, h, w);
	if (!tmp)
		return (-1);
	info.map = tmp;
	info.width = w;
	info.height = h;
	if (!find_player(tmp, h, w, &player))
	{
		free_map(tmp, h);
		return (0);
	}
	if (!flood_fill(&info, player.x, player.y))
	{
		free_map(tmp, h);
		return (0);
	}
	free_map(tmp, h);
	return (1);
}

int	parse_args(t_data *data, char *filename)
{
	if (parse_file(data, filename))
		return (1);
	if (check_map(data, filename))
		return (1);
	if (!is_map_closed(data->info_file.map, data->info_file.map_hight,
			data->info_file.map_width))
		return (ft_error("Map is not closed"), 1);
	if (is_map_closed(data->info_file.map, data->info_file.map_hight,
			data->info_file.map_width) == -1)
		return (ft_error(NULL), 1);
	if (find_player_position(data))
		return (1);
	return (0);
}
