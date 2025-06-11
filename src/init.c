#include "../inc/cub.h"

void    init_data(t_data *data)
{
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3D");
    data->img_prt = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    data->info = mlx_get_data_addr(data->img_prt, &data->bpp, &data->line_len, &data->endian);
    data->player.data = data;
    init_player(&data->player);
}

void    init_player(t_player *player)
{
    player->x = WIDTH / 2;
    player->y = HEIGHT / 2;
    player->key_up = 0;
    player->key_down = 0;
    player->key_left = 0;
    player->key_right = 0;
}