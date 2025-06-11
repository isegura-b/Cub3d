#include "../inc/cub.h"

static int is_cub_file(char *filename)
{
    int len;

    while(filename[len])
        len++;
    if (filename[len - 1] != 'b' || filename[len - 2] != 'u' || filename[len - 3] != 'c' || filename[len - 4] != '.' || len < 5)
        return (0);
    return (1);
}


static int parse_file(t_data *data, char *filename)
{
    int fd;

    if (is_cub_file(filename))
        return (ft_error("wrong file extension"), 1);
    if (open(filename, O_DIRECTORY) != -1)
        return (ft_error("not a file"), 1);
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return (ft_error("could not open file"), 1);
    close(fd);
    return (0);
}

static int check_map(t_data *data, char *filename)
{
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return (ft_error("could not open file"), 1);
    
}
int parse_args(t_data *data, char *filename)
{
    if (parse_file(data, filename))
        return (1);
    if (check_map(data, filename))
        return (1);
    return (0);
}