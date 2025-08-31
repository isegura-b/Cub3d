/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isegura- <isegura-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:01:05 by isegura-          #+#    #+#             */
/*   Updated: 2025/08/26 21:09:23 by isegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

int	is_cub_file(char *filename)
{
	int	len;

	len = 0;
	while (filename[len])
		len++;
	if (len < 5 || filename[len - 1] != 'b' || filename[len - 2] != 'u'
		|| filename[len - 3] != 'c' || filename[len - 4] != '.')
		return (0);
	return (1);
}

int	error_close(int fd, char *line)
{
	if (line)
		free(line);
	close(fd);
	return (1);
}

static void	fill_borders_with_walls(char **map, int height, int width)
{
	int		i;

	i = 0;
	while (i < width)
	{
		if (map[0][i] != '1')
			map[0][i] = '1';
		if (map[height - 1][i] != '1')
			map[height - 1][i] = '1';
		i++;
	}
	i = 0;
	while (i < height)
	{
		if (map[i][0] != '1')
			map[i][0] = '1';
		if (map[i][width - 1] != '1')
			map[i][width - 1] = '1';
		i++;
	}
}

static char	*alloc_map_row(const char *src, int width)
{
	char	*row;
	int		j;

	row = malloc(width + 1);
	if (!row)
		return (NULL);
	j = 0;
	while (src[j] && src[j] != '\n' && src[j] != '\r' && j < width)
	{
		if (src[j] == ' ' || src[j] == '\t')
			row[j] = '1';
		else
			row[j] = src[j];
		j++;
	}
	while (j < width)
	{
		row[j] = '1';
		j++;
	}
	row[width] = '\0';
	return (row);
}

int	normalize_map(t_info_file *info)
{
	char	**map;
	int		i;

	if (!info || !info->map || info->map_hight <= 0 || info->map_width <= 0)
		return (1);
	map = malloc(sizeof(char *) * (info->map_hight + 1));
	if (!map)
		return (1);
	i = 0;
	while (i < info->map_hight)
	{
		map[i] = alloc_map_row(info->map[i], info->map_width);
		if (!map[i])
		{
			free_map(map, i);
			return (1);
		}
		i++;
	}
	map[info->map_hight] = NULL;
	fill_borders_with_walls(map, info->map_hight, info->map_width);
	free_map(info->map, info->map_hight);
	info->map = map;
	return (0);
}
