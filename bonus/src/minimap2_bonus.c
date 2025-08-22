/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isegura- <isegura-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 09:09:39 by isegura-          #+#    #+#             */
/*   Updated: 2025/08/22 09:37:04 by isegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

int	mouse_move(int x, int y, t_data *data)
{
	static int	last_x;
	int			dx;
	float		sensitivity;

	sensitivity = 0.003;
	dx = 0;
	if (last_x != -1)
	{
		dx = x - last_x;
		data->player.angle += dx * sensitivity;
		if (data->player.angle > 2 * PI)
			data->player.angle -= 2 * PI;
		if (data->player.angle < 0)
			data->player.angle += 2 * PI;
	}
	last_x = x;
	(void)y;
	return (0);
}

void	draw_minimap_background(t_rect rect, int color, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < rect.w)
	{
		j = 0;
		while (j < rect.h)
		{
			my_pixel_put(rect.x + i, rect.y + j, color, data);
			j++;
		}
		i++;
	}
}

void	draw_cell_background(int x, int y, int size, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_pixel_put(x + i, y + j, 0x000000, data);
			j++;
		}
		i++;
	}
}

void	draw_map_row(char *row, int len, int y, t_minimap *m)
{
	int	x;
	int	cx;
	int	cy;

	x = 0;
	while (x < len)
	{
		cx = m->x + x * m->size;
		cy = m->y + y * m->size;
		if (row[x] != ' ' && row[x] != '\t')
			draw_cell_background(cx, cy, m->size, m->data);
		if (row[x] == '1')
			draw_square_test(cx, cy, m->size, 0xFFFFFF, m->data);
		x++;
	}
}

void	draw_minimap_cells(t_minimap *m, int height)
{
	int		y;
	int		len;
	char	*row;

	y = 0;
	while (y < height)
	{
		row = m->data->map[y];
		len = 0;
		while (row[len] && row[len] != '\n')
			len++;
		draw_map_row(row, len, y, m);
		y++;
	}
}
