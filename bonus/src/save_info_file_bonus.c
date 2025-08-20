#include "../inc/cub.h"

void    info_texture(char *line, t_info_file *info_file)
{
    char *path;
    int i = 2;

    while (line[i] == ' ')
        i++;
    path = line + i;
    if (line[0] == 'N' && line[1] == 'O')
        info_file->no = ft_strdup_path(path);
    else if (line[0] == 'S' && line[1] == 'O')
        info_file->so = ft_strdup_path(path);
    else if (line[0] == 'E' && line[1] == 'A')
        info_file->ea = ft_strdup_path(path);
    else if (line[0] == 'W' && line[1] == 'E')
        info_file->we = ft_strdup_path(path);
}

int rgb_to_int(const char *str)
{
    int r = 0;
    int g = 0;
    int b = 0;
    int i = 0;

    while (str[i] >= '0' && str[i] <= '9')
        r = r * 10 + (str[i++] - '0');
    i++;
    while (str[i] >= '0' && str[i] <= '9')
        g = g * 10 + (str[i++] - '0');
    i++;
    while (str[i] >= '0' && str[i] <= '9')
        b = b * 10 + (str[i++] - '0');
    return (r * 65536) + (g * 256) + b;
}    

void info_colors(char *line, t_info_file *info_file)
{
    int i = 1;

    while (line[i] == ' ')
        i++;
    if (line[0] == 'F')
        info_file->floor = rgb_to_int(line + i);
    else if (line[0] == 'C')
        info_file->sky = rgb_to_int(line + i);
}

size_t ft_maplen(const char *s)
{
    size_t len = 0;
    
    while (s[len] && s[len] != '\n' && s[len] != '\r')
        len++;
    return (len);
}

int ft_map(char *line, t_info_file *info_file)
{
    int j;
    char **new_map;
    int len;

    len = ft_maplen(line);
    new_map = malloc(sizeof(char *) * (info_file->map_hight + 2));
    if (!new_map)
        return (free(new_map), 1);
    if (info_file->map)
    {
        j = 0;
        while (j < info_file->map_hight)
        {
            new_map[j] = info_file->map[j];
            j++;
        }
        free(info_file->map);
    }
    new_map[info_file->map_hight] = ft_strdup(line);
    new_map[info_file->map_hight + 1] = NULL;
    info_file->map = new_map;
    if (len > info_file->map_width)
        info_file->map_width = len;
    info_file->map_hight = info_file->map_hight + 1;
    return (0);
}

int find_player_position(t_data *data)
{
    int y;
    int x;
    
    y = 0;
    while (data->map[y])
    {
        x = 0;
        while (data->map[y][x])
        {
            if (data->map[y][x] == 'N' || data->map[y][x] == 'S' || 
                data->map[y][x] == 'E' || data->map[y][x] == 'W')
            {
                data->player.x = x * WALL + WALL / 2;
                data->player.y = y * WALL + WALL / 2;

                if (data->map[y][x] == 'N')
                    data->player.angle = 3 * PI / 2;
                else if (data->map[y][x] == 'S')
                    data->player.angle = PI / 2;
                else if (data->map[y][x] == 'E')
                    data->player.angle = 0;
                else if (data->map[y][x] == 'W')
                    data->player.angle = PI;
                data->map[y][x] = '0';
                return (0);
            }
            x++;
        }
        y++;
    }
    return (ft_error("Player possition not found"), 1);
}