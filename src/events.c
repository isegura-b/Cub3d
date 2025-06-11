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
    return (0);
}

void move_player(t_player *player)
{
    int pos;
    pos = 1;

    if (player->key_up)
        player->y -= pos;
    else if (player->key_down)
        player->y += pos;
    else if (player->key_left)
        player->x -= pos;
    else if (player->key_right)
        player->x += pos;
}