#include "../inc/cub.h"

static int	premap_ready(t_info_file *i)
{
	if (!i->no || !i->so || !i->ea || !i->we)
		return (0);
	if (i->floor == -1 || i->sky == -1)
		return (0);
	return (1);
}

static int	handle_header_line(char *line, t_info_file *info, int *started)
{
	if (is_texture(line))
		info_texture(line, info);
	else if (is_color(line))
		info_colors(line, info);
	else if (is_map_line(line))
	{
		if (!premap_ready(info))
			return (ft_error("Missing textures or colors before the map"), 1);
		if (is_map_line(line) == 2)
			return (ft_error("Start of map not found"), 1);
		*started = 1;
	}
	else if (is_map_line(line) != -1 || is_texture(line) != -1
		|| is_color(line) != -1)
		return (ft_error("Invalid line format in .cub file"), 1);
	return (0);
}

static int	handle_map_line(char *line, t_info_file *info)
{
	if (ft_map(line, info))
		return (ft_error("Failed to parse map line"), 1);
	return (0);
}

static int	process_lines(int fd, t_info_file *info, int *started)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (is_empty_line(line))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (!*started && handle_header_line(line, info, started))
			return (error_close(fd, line));
		if (*started && handle_map_line(line, info))
			return (error_close(fd, line));
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!*started)
		return (ft_error("No valid map found in .cub file"), 1);
	return (0);
}

int	check_map(t_data *data, char *filename)
{
	int			fd;
	int			is_map_started;
	t_info_file	info_file;

	init_info_file(&info_file);
	is_map_started = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_error("Could not open .cub file"), 1);
	if (process_lines(fd, &info_file, &is_map_started))
		return (1);
	data->info_file = info_file;
	data->map = data->info_file.map;
	return (0);
}
