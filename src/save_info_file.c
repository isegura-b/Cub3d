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

    printf("[%s]\n",info_file->no);
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

int ft_map(char *line, t_info_file *info_file)
{
    int i;
    char **new_map;
    int len;

    i = 0;
    len = ft_strlen(line);
    new_map = malloc(sizeof(char *) * (info_file->map_hight + 2));
    if (!new_map)
        return (free(new_map), 1);
    if (info_file->map)
    {
        while (i < info_file->map_hight)
        {
            new_map[i] = info_file->map[i];
            i++;
        }
        free(info_file->map);
    }
    new_map[i] = ft_strdup(line);
    new_map[i + 1] = NULL;
    info_file->map = new_map;
    if (len > info_file->map_width)
        info_file->map_width = len;
    info_file->map_hight = info_file->map_hight + 1;
    return (0);
}