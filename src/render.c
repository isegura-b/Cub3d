#include "../inc/cub.h"

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

float distance(float x, float y)
{
    return(sqrt(x * x + y * y));
}

float ft_dis(float x1, float y1, float x2, float y2, t_data *data)
{
    float delta_x = x2 - x1;
    float delta_y = y2 - y1;
    float dist = distance(delta_x, delta_y);
    float angle = atan2(delta_y, delta_x) - data->player.angle;
    float fix_dist = dist * cos(angle);
    if (fix_dist < 0.1) // Evitar división por cero y distorsión extrema
        fix_dist = 0.1;
    return (fix_dist);
}

    //  dis = √[(x2-x1)² + (y2 - y1)²]
    //  height = tamaño pared * ocupacion en pantalla
    // 1º = tamaño de pared / dis

void draw_wall(t_player *player, t_data *data, float start_x, int i)
{
    float ray_x = player->x;
    float ray_y = player->y;
    float dis, height;
    int start_y, end, y;

    // Lanza el rayo hasta chocar con una pared
    while (!hit_ray(ray_x, ray_y, data))
    {
        ray_x += cos(start_x);
        ray_y += sin(start_x);
    }

    // Corrige distancia y calcula la altura en pantalla
    dis = ft_dis(player->x, player->y, ray_x, ray_y, data);
    height = (WALL / dis) * WIDTH;
    start_y = (HEIGHT - height) / 2;
    end = start_y + height;

    if (start_y < 0) start_y = 0;
    if (end > HEIGHT) end = HEIGHT;

    y = start_y;
    while (y < end)
    {
        int tex_x = ((int)ray_x) % 20;
        int tex_y = ((int)(ray_y + ((float)(y - start_y) / height) * WALL)) % 20; // filas de la textura

        if (tex_y < 2 || tex_x < 2)
            my_pixel_put(i, y, 0x555555, data);
        else
            my_pixel_put(i, y, 0xA0A0A0, data);

        y++;
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
    i = 0;
    start_x = player->angle - PI / 6;
    pov = (PI / 3) / WIDTH;
    while(i < WIDTH)
    {
        draw_wall(player, data, start_x, i);
        start_x += pov;
        i++;
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img_prt, 0, 0);
}