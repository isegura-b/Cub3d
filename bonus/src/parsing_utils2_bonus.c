/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isegura- <isegura-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:01:05 by isegura-          #+#    #+#             */
/*   Updated: 2025/08/17 16:02:09 by isegura-         ###   ########.fr       */
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

int	parse_file(t_data *data, char *filename)
{
	int	fd;
	int	dir_fd;

	(void)data;
	fd = open(filename, O_RDONLY);
	dir_fd = open(filename, O_DIRECTORY);
	if (dir_fd != -1)
	{
		close(dir_fd);
		return (ft_error("not a file"), 1);
	}
	if (fd == -1)
		return (ft_error("could not open file"), 1);
	close(fd);
	return (0);
}

int	is_invalid_char(char c)
{
	return (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'E' && c != 'W'
		&& c != ' ' && c != '\t' && c != '\r' && c != '\n');
}

void	free_map(char **map, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(map[i]);
		i++;
	}
	free(map);
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

static char	*alloc_rect_row(const char *src, int width)
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
	char	**rect;
	int		i;

	if (!info || !info->map || info->map_hight <= 0 || info->map_width <= 0)
		return (1);
	rect = malloc(sizeof(char *) * (info->map_hight + 1));
	if (!rect)
		return (1);
	i = 0;
	while (i < info->map_hight)
	{
		rect[i] = alloc_rect_row(info->map[i], info->map_width);
		if (!rect[i])
		{
			free_map(rect, i);
			return (1);
		}
		i++;
	}
	rect[info->map_hight] = NULL;
	fill_borders_with_walls(rect, info->map_hight, info->map_width);
	free_map(info->map, info->map_hight);
	info->map = rect;
	return (0);
}