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
	*dx = (v * c + h * s) * 3;
	*dy = (v * s + h * -c) * 3;
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
