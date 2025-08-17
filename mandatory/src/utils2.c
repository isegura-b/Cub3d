/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isegura- <isegura-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 15:34:01 by isegura-          #+#    #+#             */
/*   Updated: 2025/08/17 16:16:24 by isegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

int	get_step(const t_player *p, float *dx, float *dy)
{
	float	c;
	float	s;
	int		v;
	int		h;

	c = cos(p->angle);
	s = sin(p->angle);
	v = 0;
	h = 0;
	if (p->key_up)
		v = 1;
	else if (p->key_down)
		v = -1;
	if (p->key_left)
		h = 1;
	else if (p->key_right)
		h = -1;
	if (v == 0 && h == 0)
		return (0);
	*dx = (v * c + h * s) * 20;
	*dy = (v * s + h * -c) * 20;
	return (1);
}

void	normalize_angle(t_player *p)
{
	while (p->angle > 2 * PI)
		p->angle -= 2 * PI;
	while (p->angle < 0)
		p->angle += 2 * PI;
}

int	get_dir(const t_player *p, float *dx, float *dy)
{
	float	c;
	float	s;
	int		v;
	int		h;

	c = cos(p->angle);
	s = sin(p->angle);
	v = 0;
	h = 0;
	if (p->key_up)
		v = 1;
	else if (p->key_down)
		v = -1;
	if (p->key_left)
		h = 1;
	else if (p->key_right)
		h = -1;
	if (v == 0 && h == 0)
		return (0);
	*dx = v * c + h * s;
	*dy = v * s - h * c;
	return (1);
}

int	is_texture(char *line)
{
	int		flag;
	size_t	i;

	flag = 0;
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		flag = 1;
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		flag = 1;
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		flag = 1;
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		flag = 1;
	if (flag == 1)
	{
		i = 3;
		while (line[i] && line[i] == ' ')
			i++;
		if (!line[i] || line[i] != '.' || line[i + 1] != '/')
			return (ft_error("not path found"), -1);
		return (1);
	}
	return (0);
}
