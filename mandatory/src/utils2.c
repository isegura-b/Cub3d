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

int	ft_rep(char *line)
{
	static int	count[4];
	int			i;
	char		*id[4];

	id[0] = "NO ";
	id[1] = "SO ";
	id[2] = "EA ";
	id[3] = "WE ";
	i = -1;
	while (++i < 4)
	{
		if (!ft_strncmp(line, id[i], 3))
		{
			count[i]++;
			if (count[i] > 1)
				return (ft_error("Duplicated identifier"), -1);
			return (1);
		}
	}
	return (0);
}

int	is_texture(char *line)
{
	size_t	i;
	int		flag;

	flag = ft_rep(line);
	if (flag == -1)
		return (-1);
	if (!flag)
		return (0);
	if (flag)
	{
		i = 3;
		while (line[i] && line[i] == ' ')
			i++;
		if (!line[i] || line[i] != '.' || line[i + 1] != '/')
			return (ft_error("path not found"), -1);
	}
	return (1);
}
