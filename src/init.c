#include "../inc/cub.h"

char **get_map(void) //test sin gnl
{
    char **map = malloc(sizeof(char *) * 11);
    map[0] = "111111111111111111111111111111";
    map[1] = "100000000000000000000000000001";
    map[2] = "100000000000000000000000000001";
    map[3] = "100000000000000000000000000001";
    map[4] = "100000000000010000000000000001";
    map[5] = "100000000000000100000000000001";
    map[6] = "10000000000001000000000000000111111111111111";
    map[7] = "10000000000000000000000000000000000000000001";
    map[8] = "10000000000000000000000000000000000000000001";
    map[9] = "11111111111111111111111111111111111111111111";
    map[10] = NULL;
    return (map);
}

void load_texture(t_data *data, t_texture *tex, char *path)
{
    tex->img = mlx_xpm_file_to_image(data->mlx, path, &tex->width, &tex->height);
    if (!tex->img)
    {
        printf("Error: No se pudo cargar la textura: %s\n", path);
        exit(EXIT_FAILURE);
    }
    tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len, &tex->endian);
    if (!tex->addr)
    {
        printf("Error: No se pudo obtener la dirección de memoria de la textura: %s\n", path);
        exit(EXIT_FAILURE);
    }
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
    
    // Cargar texturas
    load_texture(data, &data->textures[NORTH], "textures/north.xpm");
    load_texture(data, &data->textures[SOUTH], "textures/south.xpm");
    load_texture(data, &data->textures[EAST], "textures/east.xpm");
    load_texture(data, &data->textures[WEST], "textures/west.xpm");
}

void    init_player(t_player *player)
{
    // Posición inicial en el centro del mapa
    player->x = WALL * 2; // 2 bloques desde el borde izquierdo
    player->y = WALL * 2; // 2 bloques desde el borde superior
    player->angle = 0; // Mirando hacia arriba (0 grados)

    player->key_up = 0;
    player->key_down = 0;
    player->key_left = 0;
    player->key_right = 0;
    player->left_r = 0;
    player->right_r = 0;
}