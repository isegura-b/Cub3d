/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isegura- <isegura-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 15:34:01 by isegura-          #+#    #+#             */
/*   Updated: 2025/08/26 21:09:00 by isegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

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
