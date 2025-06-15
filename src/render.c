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

    //  dis = √[(x2-x1)² + (y2 - y1)²]
    //  height = tamaño pared * ocupacion en pantalla
    // 1º = tamaño de pared / dis

float ft_dis(float delta_x, float delta_y, t_data *data)
{
    float dist;
    float angle;
    float fix_dist;
    dist = sqrt((delta_x * delta_x) + (delta_y * delta_y));
    angle = atan2(delta_y, delta_x) - data->player.angle;
    fix_dist = dist * cos(angle);
    return (fix_dist);
}


int    hit_ray(int x, int y, t_data *data)
{
    if (data->map[y][x] == '1')
        return (1);
    return (0);
}

void draw_wall(t_player *player, t_data *data, float start_x, int i)
{
    float ray_x = player->x;
    float ray_y = player->y;
    float dis, height;
    int start_y, end, y;
    int hit_side;
    float last_x = ray_x;
    float last_y = ray_y;

    // Lanza el rayo
    while (!hit_ray(ray_x / WALL, ray_y / WALL, data))
    {
        last_x = ray_x;
        last_y = ray_y;
        ray_x += cos(start_x);
        ray_y += sin(start_x);
    }

    //que orientacion es segun donde por donde golpea el rallo
    if ((int)(ray_x / WALL) != (int)(last_x / WALL)) // Entró desde ESTE u OESTE
    {
        if ((int)(ray_x / WALL) > (int)(last_x / WALL))
            hit_side = WEST;
        else
            hit_side = EAST;
    }
    else // Entró desde NORTE o SUR
    {
       if ((int)(ray_y / WALL) > (int)(last_y / WALL))
           hit_side = NORTH;
       else
          hit_side = SOUTH;
    }

    // Distancia y altura
    dis = ft_dis(ray_x - player->x, ray_y - player->y, data);
    height = (WALL / dis) * WIDTH;
    start_y = (int)((HEIGHT - height) / 2);
    end = (int)(start_y + height);

    // Cielo
    y = 0;
    while (y < start_y)
    {
        my_pixel_put(i, y, 0x87CEEB, data);
        y++;
    }
    // Pared
    while (y < end)
    {
    if (hit_side == NORTH)
        my_pixel_put(i, y, 0xAAAAAA, data);
    else if (hit_side == SOUTH)
        my_pixel_put(i, y, 0x0000FF, data);
    else if (hit_side == EAST)
        my_pixel_put(i, y, 0xFF0000, data);
    else
        my_pixel_put(i, y, 0x00FF00, data);
        y++;
    }

    // Suelo
    while (y < HEIGHT)
    {
        my_pixel_put(i, y, 0x228B22, data);
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