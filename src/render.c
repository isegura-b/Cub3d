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

    // Corrige la distancia y calcula la altura de la pared
    dis = ft_dis(player->x, player->y, ray_x, ray_y, data);
    height = (WALL / dis) * WIDTH;
    start_y = (HEIGHT - height) / 2;
    end = start_y + height;

    if (start_y < 0) start_y = 0;
    if (end > HEIGHT) end = HEIGHT;

    // Coordenada del impacto para la textura
    float wall_x;
    if (fabs(cos(start_x)) > fabs(sin(start_x)))
        wall_x = ray_y;
    else
        wall_x = ray_x;
    wall_x -= floor(wall_x); // Fracción

    float center_line_ratio = 0.05; // 5% del alto de la pared
    int center_line_thickness = (int)(height * center_line_ratio);
    if (center_line_thickness < 1) center_line_thickness = 1;
    int line_thickness = 10; // Grosor de la línea superior/inferior (puedes ajustar si quieres)
    y = start_y;
    while (y < end)
    {
        // Solo líneas horizontales y fondo
        if (
            (y - start_y < line_thickness) || // Línea superior
            (y - start_y > height - line_thickness - 1) || // Línea inferior
            (abs((y - start_y) - height / 2) < center_line_thickness / 2) // Línea central proporcional
        )
            my_pixel_put(i, y, 0xFF0000, data); // Rojo para las líneas horizontales
        else
            my_pixel_put(i, y, 0xAAAAAA, data); // Gris claro para la pared

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