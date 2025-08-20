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

int     hit_ray(int x, int y, t_data *data)
{
    if (y < 0 || y >= HEIGHT || x < 0 || x >= WIDTH)
        return (1);
    if (data->map[y][x] == '1')
        return (1);
    return (0);
}

int     get_tex_pixel(t_texture *tex, int x, int y) 
{
    return (*(unsigned int *)(tex->addr + (y * tex->line_len + x * (tex->bpp / 8))));
}

void    draw_wall(t_player *player, t_data *data, float angle, int i)
{
    t_hit_info hit;

    cast_ray(player, data, angle, &hit);
    hit.distance = hit.distance * cos(angle - player->angle);
    hit.height = (WALL / hit.distance) * 1000;
    hit.start_y = (int)((HEIGHT - hit.height) / 2);
    hit.end_y = (int)(hit.start_y + hit.height);
    draw_column(&hit, i, data);
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
    draw_minimap(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img_prt, 0, 0);
    return (0);
}