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

static int	check_map(t_data *data, char *filename)
{
	int			fd;
	char		*line;
	int			is_map_started;
	t_info_file	info_file;

	is_map_started = 0;
	init_info_file(&info_file);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_error("Could not open .cub file"), 1);
	while ((line = get_next_line(fd)) != NULL)
	{
		if (is_empty_line(line))
		{
			free(line);
			continue ;
		}
		if (!is_map_started)
		{
			if (is_texture(line))
				info_texture(line, &info_file);
			else if (is_color(line))
				info_colors(line, &info_file);
			else if (is_map_line(line))
			{
				if (!info_file.no || !info_file.so || !info_file.ea
					|| !info_file.we || info_file.floor == -1
					|| info_file.sky == -1)
				{
					free(line);
					close(fd);
					return (ft_error("Missing textures or colors before the map"),
						1);
				}
				else if (is_map_line(line) == 2)
				{
					free(line);
					close(fd);
					return (ft_error("Start of map not found"), 1);
				}
				is_map_started = 1;
			}
			else if (is_map_line(line) != -1 || is_texture(line) != -1
				|| is_color(line) != -1)
			{
				free(line);
				close(fd);
				return (ft_error("Invalid line format in .cub file"), 1);
			}
		}
		if (is_map_started)
		{
			if (ft_map(line, &info_file))
			{
				free(line);
				close(fd);
				return (ft_error("Failed to parse map line"), 1);
			}
		}
		free(line);
	}
	close(fd);
	if (!is_map_started)
		return (ft_error("No valid map found in .cub file"), 1);
	data->info_file = info_file;
	data->map = data->info_file.map;
	return (0);
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
