#include "../inc/cub.h"
#define MINIMAP_SCALE 0.2
#define MINIMAP_OFFSET_X 20
#define MINIMAP_OFFSET_Y 20
#define MINIMAP_RAYS 60
#define PLAYER_SIZE 6
#define MAP_BORDER_COLOR 0xC2B280
#define MAP_CORNER_COLOR 0x8B7B4A

typedef struct s_rect {
    int x;
    int y;
    int w;
    int h;
} t_rect;

typedef struct s_minimap {
    int x;
    int y;
    int size;
    t_data *data;
} t_minimap;

void draw_square_test(int x, int y, int size, int color, t_data *data)
{
    int i;
    i = 0;
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

static void draw_minimap_background(t_rect rect, int color, t_data *data)
{
    int i;
    int j;

    i = 0;
    while (i  < rect.w)
    {
        j = 0;
        while (j < rect.h)
        {
            my_pixel_put(rect.x + i, rect.y + j, color, data);
            j++;
        }
        i++;
    }
}

static void draw_cell_background(int x, int y, int size, t_data *data)
{
    int i;
    int j;

    i = 0;
    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            my_pixel_put(x + i, y + j, 0x000000, data);
            j++;
        }
        i++;
    }
}

static void draw_map_row(char *row, int len, int y, t_minimap *m)
{
    int x;
    int cx;
    int cy;

    x = 0;
    while (x < len)
    {
        cx = m->x + x * m->size;
        cy = m->y + y * m->size;
        if (row[x] != ' ' && row[x] != '\t')
            draw_cell_background(cx, cy, m->size, m->data);
        if (row[x] == '1')
            draw_square_test(cx, cy, m->size, 0xFFFFFF, m->data);
        x++;
    }
}

static void draw_minimap_cells(t_minimap *m, int height)
{
    int y;
    int len;
    char *row;

    y = 0;
    while (y < height)
    {
        row = m->data->map[y];
        len = 0;
        while (row[len] && row[len] != '\n')
            len++;
        draw_map_row(row, len, y, m);
        y++;
    }
}

static void draw_minimap_player(t_minimap *m)
{
    int px;
    int py;

    px = m->x + (int)(m->data->player.x / WALL * m->size);
    py = m->y + (int)(m->data->player.y / WALL * m->size);
    draw_square_test(px - PLAYER_SIZE / 2, py - PLAYER_SIZE / 2, PLAYER_SIZE, 0x00FF00, m->data);
}

static int minimap_hit_ray(float x, float y, t_data *data)
{
    int cx;
    int cy;

    cx = x / WALL;
    cy = y / WALL;

    if (cy < 0 || cx < 0)
        return 1;
    if (!data->map[cy] || !data->map[cy][cx])
        return 1;
    if (data->map[cy][cx] == '1')
        return 1;
    return 0;
}

static void draw_ray(float angle, t_minimap *m)
{
    float rx;
    float ry;
    int mx;
    int my;

    rx = m->data->player.x;
    ry = m->data->player.y;

    while (!minimap_hit_ray(rx, ry, m->data))
    {
        mx = m->x + (int)(rx / WALL * m->size);
        my = m->y + (int)(ry / WALL * m->size);
        my_pixel_put(mx, my, 0xFF0000, m->data);
        rx += cos(angle);
        ry += sin(angle);
    }
}

static void draw_minimap_rays(t_minimap *m)
{
    int i;
    float angle;
    float step;

    angle = m->data->player.angle - (PI / 6);
    step = (PI / 3) / MINIMAP_RAYS;
    i = 0;
    while (i < MINIMAP_RAYS)
    {
        draw_ray(angle, m);
        angle += step;
        i++;
    }
}

static void draw_minimap_corners(int min_x, int min_y, int w, int h, int s, int t, int c, t_data *data)
{
    t_rect corner;

    corner.w = c;
    corner.h = c;

    corner.x = min_x - t;
    corner.y = min_y - t;
    draw_minimap_background(corner, MAP_CORNER_COLOR, data);

    corner.x = min_x + w * s + t - c;
    corner.y = min_y - t;
    draw_minimap_background(corner, MAP_CORNER_COLOR, data);

    corner.x = min_x - t;
    corner.y = min_y + h * s + t - c;
    draw_minimap_background(corner, MAP_CORNER_COLOR, data);

    corner.x = min_x + w * s + t - c;
    corner.y = min_y + h * s + t - c;
    draw_minimap_background(corner, MAP_CORNER_COLOR, data);
}

void draw_minimap(t_data *data)
{
    int width;
    int height;
    int size;
    t_rect frame;
    t_minimap m;

    width = data->info_file.map_width;
    height = data->info_file.map_hight;
    if (height > width)
        width = height;
    size = 200 / width;
    m.x = WIDTH - (width * size) - MINIMAP_OFFSET_X;
    m.y = HEIGHT - (height * size) - MINIMAP_OFFSET_Y;   
    m.size = size;
    m.data = data;
    frame.x = m.x - 10;
    frame.y = m.y - 10;
    frame.w = width * size + 10 * 2;
    frame.h = height * size + 10 * 2;
    draw_minimap_background(frame, MAP_BORDER_COLOR, data);
    draw_minimap_corners(m.x, m.y, width, height, size, 10, 14, data);
    draw_minimap_cells(&m, height);
    draw_minimap_rays(&m);
    draw_minimap_player(&m);
}

