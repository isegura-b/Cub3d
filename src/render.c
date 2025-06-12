#include "../inc/cub.h"

void draw_square_test(int x, int y, int size, int color, t_data *data)
{
    int i = 0;

    while (i < size)
    {
        if (x + i >= 0 && x + i < WIDTH && y >= 0 && y < HEIGHT)
            my_pixel_put(x + i, y, color, data); 
        if (x >= 0 && x < WIDTH && y + i >= 0 && y + i < HEIGHT)
            my_pixel_put(x, y + i, color, data);
        if (x + size - 1 >= 0 && x + size - 1 < WIDTH && y + i >= 0 && y + i < HEIGHT)
            my_pixel_put(x + size - 1, y + i, color, data);
        if (x + i >= 0 && x + i < WIDTH && y + size - 1 >= 0 && y + size - 1 < HEIGHT)
            my_pixel_put(x + i, y + size - 1, color, data);
        i++;
    }
}

void    clean_img(t_data *data)
{
    int y;
    int x;

    y = 0;
    while(y < HEIGHT)
    {
        x = 0;
        while(x < WIDTH)
        {
            my_pixel_put(x, y, 0, data);
            x++;
        }
        y++;
    }
}

void    draw_map(t_data *data)
{
    char    **map;
    int     y;
    int     x;

    map = data->map;
    y = 0;
    while (map[y])
    {
        x = 0;
        while (map[y][x])
        {
            if (map[y][x] == '1')
                draw_square_test(x * WALL, y * WALL, WALL, 0xFFFFFF, data);
            x++;
        }
        y++;
    }
}

int    hit_ray(float px, float py, t_data *data)
{
    int     x;
    int     y;

    x = px / WALL;
    y = py / WALL; 
    if (data->map[y][x] == '1')
        return (1);
    return (0);
}

void    draw_ray(t_player *player, t_data *data, float start_x, int i)
{
    float       ray_x;
    float       ray_y;
    float       cos_ang;
    float       sin_ang;

    ray_x = player->x;
    ray_y = player->y;
    cos_ang = cos(player->angle);
    sin_ang = sin(player->angle);

    while (!hit_ray(ray_x, ray_y, data)) //para ver si pega antes por x o por y
    {
        my_pixel_put(ray_x, ray_y, 0xFF0000, data);
        ray_x += cos(start_x);
        ray_y += sin(start_x);
    }
}

int     draw_loop(t_data *data)
{
    t_player    *player;
    int         i;
    float       start_x;
    float       pov;

    player = &data->player;
    move_player(player);
    clean_img(data);
    draw_square_test(player->x - 10 / 2, player->y - 10 / 2, 10, 0x00FF00, data);
    draw_map(data);
    i = 0;
    start_x = player->angle - PI / 6;
    pov = (PI / 6) / WIDTH; // 30º / pantalla
    while(i < WIDTH)
    {
        draw_ray(player, data, start_x, i);
        start_x += pov;
        i++;
    }

    mlx_put_image_to_window(data->mlx, data->win, data->img_prt, 0, 0);
}