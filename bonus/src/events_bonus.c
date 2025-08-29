/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isegura- <isegura-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:51:36 by isegura-          #+#    #+#             */
/*   Updated: 2025/08/17 13:51:45 by isegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

int	window_close(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img_prt);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(EXIT_SUCCESS);
}

int	key_press(int keycode, t_player *player)
{
	if (keycode == ESC)
		window_close(player->data);
	if (keycode == W)
		player->key_up = 1;
	if (keycode == A)
		player->key_left = 1;
	if (keycode == S)
		player->key_down = 1;
	if (keycode == D)
		player->key_right = 1;
	if (keycode == LEFT)
		player->left_r = 1;
	if (keycode == RIGHT)
		player->right_r = 1;
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = 0;
	if (keycode == A)
		player->key_left = 0;
	if (keycode == S)
		player->key_down = 0;
	if (keycode == D)
		player->key_right = 0;
	if (keycode == LEFT)
		player->left_r = 0;
	if (keycode == RIGHT)
		player->right_r = 0;
	return (0);
}

int	wall_stop(t_player *player)
{
	float	dx;
	float	dy;
	int		map_x;
	int		map_y;

	if (!get_step(player, &dx, &dy))
		return (0);
	map_x = (int)((player->x + dx) / WALL);
	map_y = (int)((player->y + dy) / WALL);
	if (map_x < 0 || map_y < 0
		|| map_y >= player->data->info_file.map_hight
		|| map_x >= player->data->info_file.map_width)
		return (1);
	if (player->data->map[map_y][map_x] == '1')
		return (1);
	return (0);
}

void	move_player(t_player *player)
{
	int		speed;
	float	dx;
	float	dy;

	speed = 6;
	if (player->left_r)
		player->angle -= 0.05f;
	if (player->right_r)
		player->angle += 0.05f;
	normalize_angle(player);
	if (get_dir(player, &dx, &dy) && !wall_stop(player))
	{
		player->x += dx * speed;
		player->y += dy * speed;
	}
}
