#include "../inc/cub.h"

static int is_cub_file(char *filename)
{
	int len = 0;
	while (filename[len])
		len++;
	if (len < 5 || filename[len - 1] != 'b' || filename[len - 2] != 'u'
		|| filename[len - 3] != 'c' || filename[len - 4] != '.')
		return (0);
	return (1);
}

static int parse_file(t_data *data, char *filename)
{
	int fd = open(filename, O_RDONLY);
	int dir_fd = open(filename, O_DIRECTORY);

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

static int is_invalid_char(char c)
{
    return (c != '0' && c != '1' && c != 'N' && c != 'S'
        && c != 'E' && c != 'W' && c != ' ' && c != '\t' && c != '\r' && c != '\n');
}

static void free_map(char **map, int height)
{
	int i = 0;
	while (i < height)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

static int flood_fill(char **map, int x, int y, int width, int height)
{
	if (x < 0 || y < 0 || x >= width || y >= height)
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'F')
		return (1);
	if (map[y][x] == ' ')
		return (0);
	if (is_invalid_char(map[y][x]))
		return (0);
	map[y][x] = 'F';
	if (!flood_fill(map, x + 1, y, width, height)) return (0);
	if (!flood_fill(map, x - 1, y, width, height)) return (0);
	if (!flood_fill(map, x, y + 1, width, height)) return (0);
	if (!flood_fill(map, x, y - 1, width, height)) return (0);
	return (1);
}

static char **copy_map(char **map, int height, int width)
{
	char **copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);

	int i = 0;
	while (i < height)
	{
		copy[i] = malloc(width + 1);
		if (!copy[i])
			return (NULL);
		int j = 0;
		while (j < width && map[i][j])
		{
			if (is_invalid_char(map[i][j]))
			{
				printf("Invalid char in map: '%c' (ASCII: %d) en fila %d, columna %d\n", map[i][j], (int)map[i][j], i, j);
				free_map(copy, i + 1);
				return (NULL);
			}
			copy[i][j] = map[i][j];
			j++;
		}
		while (j < width)
			copy[i][j++] = ' ';
		copy[i][j] = '\0';
		i++;
	}
	copy[height] = NULL;
	return (copy);
}

int is_map_closed(char **map, int height, int width)
{
	char **temp = copy_map(map, height, width);
	if (!temp)
		return (-1);

	int i = 0;
	int x = -1, y = -1;
	while (i < height && y == -1)
	{
		int j = 0;
		while (j < width)
		{
			if (temp[i][j] == 'N' || temp[i][j] == 'S'
				|| temp[i][j] == 'E' || temp[i][j] == 'W')
			{
				y = i;
				x = j;
				break;
			}
			j++;
		}
		i++;
	}
	if (x == -1 || y == -1)
	{
		free_map(temp, height);
		return (0);
	}
	int result = flood_fill(temp, x, y, width, height);
	free_map(temp, height);
	return (result);
}


static int check_map(t_data *data, char *filename)
{
	int fd;
	char *line;
	int is_map_started = 0;
	t_info_file info_file;

	init_info_file(&info_file);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_error("Could not open .cub file"), 1);
	while ((line = get_next_line(fd)) != NULL)
	{
		if (is_empty_line(line))
		{
			free(line);
			continue;
		}
		if (!is_map_started)
		{
			if (is_texture(line))
				info_texture(line, &info_file);
			else if (is_color(line))
				info_colors(line, &info_file);
			else if (is_map_line(line))
			{
				if (!info_file.no || !info_file.so || !info_file.ea || !info_file.we
					|| info_file.floor == -1 || info_file.sky == -1)
				{
					free(line);
					close(fd);
					return (ft_error("Missing textures or colors before the map"), 1);
				}
				else if (is_map_line(line) == 2)
				{
					free(line);
					close(fd);
					return (ft_error("Start of map not found"), 1);
				}
				is_map_started = 1;
			}
			else if (is_map_line(line) != -1 || is_texture(line) != -1 || is_color(line) != -1)
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

int parse_args(t_data *data, char *filename)
{
	if (parse_file(data, filename))
		return (1);
	if (check_map(data, filename))
		return (1);
	if (!is_map_closed(data->info_file.map, data->info_file.map_hight, data->info_file.map_width))
		return (ft_error("Map is not closed"), 1);
	if (is_map_closed(data->info_file.map, data->info_file.map_hight, data->info_file.map_width) == -1)
		return (ft_error(NULL), 1);
	if (find_player_position(data))
		return (1);
	return (0);
}
