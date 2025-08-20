#include "../inc/cub.h"

int is_empty_line(const char *line)
{
	int	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' &&
			line[i] != '\n' && line[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}

int is_texture(char *line)
{
    int flag;
    int i;

    flag = 0;
    if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
        flag = 1;
    else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
        flag = 1;
    else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
        flag = 1;
    else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
        flag = 1;
    if (flag == 1)
    {
        i = 3;
        while (line[i] && line[i] == ' ')
            i++;
        if (!line[i] || line[i] != '.' || line[i + 1] != '/')
            return (ft_error("not path found") , -1);
        return (1);
    }
    else
        return (0);
}


int is_valid_rgb(const char *str)
{
    int i;
    int j;
    int num;

    i = 0;
    j = 0;
    while (j < 3)
    {
        if (!(str[i] >= '0' && str[i] <= '9'))
            return (0);
        num = 0;
        while (str[i] >= '0' && str[i] <= '9')
        {
            num = num * 10 + (str[i] - '0');
            i++;
        }
        if (num < 0 || num > 255)
            return (0);
        j++;
        if (j < 3)
        {
            if (str[i] != ',')
                return (0);
            i++;
        }
    }
    while (str[i] == ' ' || str[i] == '\n' || str[i] == '\r')
        i++;
    if (str[i] != '\0')
        return (0);
    return (1);
}


int is_color(char *line)
{
    int i;

    i = 1;
    while (line[i] == ' ')
        i++;
    if (line[0] == 'F')
    {
        if (line[i] == '\0')
            return (ft_error("Floor has no color"), -1);
        if (!is_valid_rgb(line + i))
            return (ft_error("Floor color must be in R,G,B format (0-255)"), -1);
        return (1);
    }
    else if (line[0] == 'C')
    {
        if (line[i] == '\0')
            return (ft_error("Sky has no color"),-1);
        if (!is_valid_rgb(line + i))
            return (ft_error("Sky color must be in R,G,B format (0-255)"), -1);
        return (1);
    }
    return (0);
}

int is_map_line(char *line)
{
    int i; 
    
    i = 0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    while (line[i])
    {
        if (line[i] != '1' && line[i] != ' ' && line[i] != '\n' && line[i] != '\r') 
        {
            return(2);
        }
        i++;
    }
    return (1);
}