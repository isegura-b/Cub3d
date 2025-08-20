#include "../inc/cub.h"

void	ft_error(char *error_str)
{
    if (error_str)
	    printf("Error : %s\n", error_str);
	exit(EXIT_FAILURE);
}

void	my_pixel_put(int x, int y, int color, t_data *img)
{
	int	offset;
    
	if(x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
        return;
	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->info + offset) = color;
}

int	handle_exit(void *param)
{
	cleanup_data((t_data *)param);
	exit(0);
	return (0);
}

char    *ft_strdup(const char *s)
{
    size_t  len = 0;
    char    *copy;

    while (s[len])
        len++;
    copy = (char *)malloc(len + 1);
    if (!copy)
        return (NULL);
    size_t i = 0;
    while (i <= len)
    {
        copy[i] = s[i];
        i++;
    }
    return (copy);
}

char    *ft_strdup_path(const char *s)
{
    size_t  len;
    char    *copy;

    len = 0;
    while (s[len] && s[len] != ' ' && s[len] != '\n' && s[len] != '\r')
        len++;
    copy = (char *)malloc(len + 1);
    if (!copy)
        return (NULL);
    size_t i = 0;
    while (i < len)
    {
        copy[i] = s[i];
        i++;
    }
    copy[len] = '\0';
    return (copy);
}