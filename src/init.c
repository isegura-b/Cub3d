#include "../inc/cub.h"

char **get_map(void) //test sin gnl
{
    char **map = malloc(sizeof(char *) * 11);
    map[0] = "111111111111111";
    map[1] = "100000001000001";
    map[2] = "100000001000001";
    map[3] = "100000100001001";
    map[4] = "100000000000001";
    map[5] = "100000000000001";
    map[6] = "100001000000001";
    map[7] = "100000000001001";
    map[8] = "100000000000001";
    map[9] = "111111111111111";
    map[10] = NULL;
    return (map);
}

void    init_data(t_data *data)
{
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3D");
    data->img_prt = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    data->info = mlx_get_data_addr(data->img_prt, &data->bpp, &data->line_len, &data->endian);
    data->player.data = data;
    data->map = get_map(); //gnl
    init_player(&data->player);
}

void    init_player(t_player *player)
{
    //por programar
    player->x = WIDTH / 2; //posicion de spawn
    player->y = HEIGHT / 2;
    player->angle = PI * 1.5; //direccion de spawn

    player->key_up = 0;
    player->key_down = 0;
    player->key_left = 0;
    player->key_right = 0;
    player->left_r = 0;
    player->right_r = 0;
}