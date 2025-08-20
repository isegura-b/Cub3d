/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_tex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprenafe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 14:11:27 by aprenafe          #+#    #+#             */
/*   Updated: 2025/08/17 14:36:07 by isegura-         ###   ########.fr       */
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

void	draw_tex_wall(t_wall_info *w)
{
	t_wall_calc	c;

	c.wall_height = w->hit->end_y - w->hit->start_y;
	c.y = w->hit->start_y;
	while (c.y < w->hit->end_y)
	{
		c.d = c.y - w->hit->start_y;
		c.tex_y = (int)((float)c.d / c.wall_height * w->tex->height);
		if (c.tex_y < 0)
			c.tex_y = 0;
		if (c.tex_y >= w->tex->height)
			c.tex_y = w->tex->height - 1;
		c.color = get_tex_pixel(w->tex, w->tex_x, c.tex_y);
		my_pixel_put(w->x, c.y, c.color, w->data);
		c.y++;
	}
}

void	draw_column(t_hit_info *hit, int i, t_data *data)
{
	float		wall_x;
	t_texture	tex;
	int			tex_x;
	t_wall_info	w;

	wall_x = get_wall_hit_x(hit);
	tex = data->textures[hit->hit_side];
	tex_x = get_tex_x(wall_x, hit->hit_side, &tex);
	draw_sky(i, hit->start_y, data);
	w.hit = hit;
	w.x = i;
	w.tex = &tex;
	w.tex_x = tex_x;
	w.data = data;
	draw_tex_wall(&w);
	draw_floor(i, hit->end_y, data);
}
