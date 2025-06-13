#include "../inc/cub.h"

int	window_close(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img_prt);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(EXIT_SUCCESS);
}

int key_press(int keycode, t_player *player) //poder mantener presionado
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

int key_release(int keycode, t_player *player)
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

int wall_stop(t_player *player)
{
    float next_x;
    float next_y;
    int map_x;
    int map_y;

    // Calculamos la siguiente posición basada en la dirección del movimiento
    if (player->key_up)
    {
        next_x = player->x + cos(player->angle) * 3;
        next_y = player->y + sin(player->angle) * 3;
    }
    else if (player->key_down)
    {
        next_x = player->x - cos(player->angle) * 3;
        next_y = player->y - sin(player->angle) * 3;
    }
    else if (player->key_left)
    {
        next_x = player->x + sin(player->angle) * 3;
        next_y = player->y - cos(player->angle) * 3;
    }
    else if (player->key_right)
    {
        next_x = player->x - sin(player->angle) * 3;
        next_y = player->y + cos(player->angle) * 3;
    }
    else
        return 0;
    map_x = (int)(next_x / WALL);
    map_y = (int)(next_y / WALL);
    if (player->data->map[map_y][map_x] == '1')
        return 1;
    return 0;
}

void move_player(t_player *player)
{
    int     speed; 
    float   angle_speed;
    float   cos_angle;
    float   sin_angle;

    angle_speed = 0.04;
    speed = 4;
    cos_angle = cos(player->angle);
    sin_angle = sin(player->angle);
    //angulo
    if (player->left_r)
        player->angle -= angle_speed;
    if (player->right_r)
        player->angle += angle_speed;
    //2pi angulos max
    if (player->angle > 2 * PI)
        player->angle = 0;
    if (player->angle < 0)
        player->angle = 2 * PI;
    //angulo hacia donde avanza (papel)
    if (player->key_up && !wall_stop(player))
    {
        player->x += cos_angle * speed;
        player->y += sin_angle * speed;
    }
    else if (player->key_down && !wall_stop(player))
    {
        player->x -= cos_angle * speed;
        player->y -= sin_angle * speed;
    }
    else if (player->key_left && !wall_stop(player))
    {
        player->x += sin_angle * speed;
        player->y -= cos_angle * speed;
    }
    else if (player->key_right && !wall_stop(player))
    {
        player->x -= sin_angle * speed;
        player->y += cos_angle * speed;
    }
}