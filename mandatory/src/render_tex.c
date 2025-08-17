/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_tex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprenafe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 14:11:27 by aprenafe          #+#    #+#             */
/*   Updated: 2025/08/17 14:11:32 by aprenafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

float	get_wall_hit_x(t_hit_info *hit)
{
	float	result;

	if (hit->hit_side == NORTH || hit->hit_side == SOUTH)
		result = hit->ray_x / WALL - floor(hit->ray_x / WALL);
	else
		result = hit->ray_y / WALL - floor(hit->ray_y / WALL);
	return (result);
}

int	get_tex_x(float wall_x, int side, t_texture *tex)
{
	int	tex_x;

	tex_x = (int)(wall_x * tex->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	if (side == EAST || side == SOUTH)
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

void	draw_sky(int x, int end_y, t_data *data)
{
	int	y;

	y = 0;
	while (y < end_y)
	{
		my_pixel_put(x, y, data->info_file.sky, data);
		y++;
	}
}

void	draw_floor(int x, int start_y, t_data *data)
{
	int	y;

	y = start_y;
	while (y < HEIGHT)
	{
		my_pixel_put(x, y, data->info_file.floor, data);
		y++;
	}
}

void	draw_tex_wall(t_hit_info *hit, int x, t_texture *tex, int tex_x,
		t_data *data)
{
	int	wall_height;
	int	y;
	int	d;
	int	tex_y;
	int	color;

	wall_height = hit->end_y - hit->start_y;
	y = hit->start_y;
	while (y < hit->end_y)
	{
		d = y - hit->start_y;
		tex_y = (int)((float)d / wall_height * tex->height);
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		color = get_tex_pixel(tex, tex_x, tex_y);
		my_pixel_put(x, y, color, data);
		y++;
	}
}

void	draw_column(t_hit_info *hit, int i, t_data *data)
{
	float		wall_x;
	t_texture	tex;
	int			tex_x;

	wall_x = get_wall_hit_x(hit);
	tex = data->textures[hit->hit_side];
	tex_x = get_tex_x(wall_x, hit->hit_side, &tex);
	draw_sky(i, hit->start_y, data);
	draw_tex_wall(hit, i, &tex, tex_x, data);
	draw_floor(i, hit->end_y, data);
}
