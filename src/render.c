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

int     draw_loop(t_data *data)
{
    t_player    *player;

    player = &data->player;
    move_player(player);
    clean_img(data);
    draw_square_test(player->x, player->y, 10, 0x00FF00, data);
    mlx_put_image_to_window(data->mlx, data->win, data->img_prt, 0, 0);
}