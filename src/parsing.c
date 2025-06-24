#include "../inc/cub.h"

static int is_cub_file(char *filename)
{
    int len;

    len = 0;
    while(filename[len])
        len++;
    if (filename[len - 1] != 'b' || filename[len - 2] != 'u' || filename[len - 3] != 'c' || filename[len - 4] != '.' || len < 5)
        return (0);
    return (1);
}


static int parse_file(t_data *data, char *filename)
{
    int fd;
    int dir_fd;

    dir_fd = open(filename, O_DIRECTORY);
    if (dir_fd != -1)
    {
        close(dir_fd);
        return (ft_error("not a file"), 1);
    }
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return (ft_error("could not open file"), 1);
    close(fd);
    return (0);
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
			continue;
		}
		if (is_map_started == 0)
		{
			if (is_texture(line))
				info_texture(line, &info_file);
			else if (is_color(line))
				info_colors(line, &info_file);
			else if (is_map_line(line))
			{
				if (!info_file.no || !info_file.so || !info_file.ea || !info_file.we ||
					info_file.floor == -1 || info_file.sky == -1)
				{
					free(line);
					close(fd);
					return (ft_error("Missing textures or colors before the map"), 1);
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
    if (find_player_position(data))
		return (1);
    return (0);
}