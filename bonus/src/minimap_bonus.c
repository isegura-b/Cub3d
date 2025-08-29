/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isegura- <isegura-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 09:18:38 by isegura-          #+#    #+#             */
/*   Updated: 2025/08/22 11:11:44 by isegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

static void	draw_minimap_player(t_minimap *m)
{
	int		px;
	int		py;
	t_point	point;

	px = m->x + (int)(m->data->player.x / WALL * m->size);
	py = m->y + (int)(m->data->player.y / WALL * m->size);
	point.x = px - (PLAYER_SIZE / 2);
	point.y = py - (PLAYER_SIZE / 2);
	draw_square_test(point, PLAYER_SIZE,
		0x00FF00, m->data);
}

static int	minimap_hit_ray(float x, float y, t_data *data)
{
	int	cx;
	int	cy;

	cx = x / WALL;
	cy = y / WALL;
	if (cy < 0 || cx < 0)
		return (1);
	if (!data->map[cy] || !data->map[cy][cx])
		return (1);
	if (data->map[cy][cx] == '1')
		return (1);
	return (0);
}

static void	draw_ray(float angle, t_minimap *m)
{
	float	rx;
	float	ry;
	int		mx;
	int		my;

	rx = m->data->player.x;
	ry = m->data->player.y;
	while (!minimap_hit_ray(rx, ry, m->data))
	{
		mx = m->x + (int)(rx / WALL * m->size);
		my = m->y + (int)(ry / WALL * m->size);
		my_pixel_put(mx, my, 0xFF0000, m->data);
		rx += cos(angle);
		ry += sin(angle);
	}
}

static void	draw_minimap_rays(t_minimap *m)
{
	int		i;
	float	angle;
	float	step;

	angle = m->data->player.angle - (PI / 6);
	step = (PI / 3) / MINIMAP_RAYS;
	i = 0;
	while (i < MINIMAP_RAYS)
	{
		draw_ray(angle, m);
		angle += step;
		i++;
	}
}

void	draw_minimap(t_data *data)
{
	int			width;
	int			height;
	int			size;
	t_rect		frame;
	t_minimap	m;

	width = data->info_file.map_width;
	height = data->info_file.map_hight;
	if (height > width)
		width = height;
	size = 200 / width;
	m.x = WIDTH - (width * size) - MINIMAP_OFFSET_X;
	m.y = HEIGHT - (height * size) - MINIMAP_OFFSET_Y;
	m.size = size;
	m.data = data;
	frame.x = m.x - 10;
	frame.y = m.y - 10;
	frame.w = width * size + 10 * 2;
	frame.h = height * size + 10 * 2;
	draw_minimap_background(frame, MAP_BORDER_COLOR, data);
	draw_minimap_cells(&m, height);
	draw_minimap_rays(&m);
	draw_minimap_player(&m);
}
