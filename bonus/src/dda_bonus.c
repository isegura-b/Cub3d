#include "../inc/cub.h"

void	perform_dda(t_ray_vars *var, t_data *data)
{
	var->hit_wall = 0;
	while (!var->hit_wall)
	{
		if (var->side_dist_x < var->side_dist_y)
		{
			var->side_dist_x += var->delta_dist_x;
			var->map_x += var->step_x;
			var->side = 0;
		}
		else
		{
			var->side_dist_y += var->delta_dist_y;
			var->map_y += var->step_y;
			var->side = 1;
		}
		if (hit_ray(var->map_x, var->map_y, data))
			var->hit_wall = 1;
	}
}

void	calculate_hit_info(t_hit_info *hit, t_ray_vars *var)
{
	if (var->side == 0)
		hit->distance = (var->map_x * WALL - var->pos_x + (1 - var->step_x)
			/ 2.0f * WALL) / var->ray_dir_x;
	else
		hit->distance = (var->map_y * WALL - var->pos_y + (1 - var->step_y)
			/ 2.0f * WALL) / var->ray_dir_y;
	hit->ray_x = var->pos_x + hit->distance * var->ray_dir_x;
	hit->ray_y = var->pos_y + hit->distance * var->ray_dir_y;
	if (var->side == 0)
	{
		if (var->ray_dir_x < 0)
			hit->hit_side = WEST;
		else
			hit->hit_side = EAST;
	}
	else
	{
		if (var->ray_dir_y < 0)
			hit->hit_side = NORTH;
		else
			hit->hit_side = SOUTH;
	}
}

void	init_ray_steps(t_ray_vars *var)
{
	if (var->ray_dir_x < 0)
	{
		var->step_x = -1;
		var->side_dist_x = (var->pos_x - var->map_x * WALL) * var->delta_dist_x
			/ WALL;
	}
	else
	{
		var->step_x = 1;
		var->side_dist_x = ((var->map_x + 1) * WALL - var->pos_x)
			* var->delta_dist_x / WALL;
	}
	if (var->ray_dir_y < 0)
	{
		var->step_y = -1;
		var->side_dist_y = (var->pos_y - var->map_y * WALL) * var->delta_dist_y
			/ WALL;
	}
	else
	{
		var->step_y = 1;
		var->side_dist_y = ((var->map_y + 1) * WALL - var->pos_y)
			* var->delta_dist_y / WALL;
	}
}

void	init_ray_vars(t_ray_vars *var, t_player *player, float angle)
{
	var->pos_x = player->x;
	var->pos_y = player->y;
	var->map_x = (int)(var->pos_x / WALL);
	var->map_y = (int)(var->pos_y / WALL);
	var->ray_dir_x = cos(angle);
	var->ray_dir_y = sin(angle);
	var->delta_dist_x = fabs(WALL / var->ray_dir_x);
	var->delta_dist_y = fabs(WALL / var->ray_dir_y);
}

void	cast_ray(t_player *player, t_data *data, float angle, t_hit_info *hit)
{
	t_ray_vars	var;

	init_ray_vars(&var, player, angle);
	init_ray_steps(&var);
	perform_dda(&var, data);
	calculate_hit_info(hit, &var);
}
