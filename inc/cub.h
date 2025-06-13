#ifndef CUB_H
#define CUB_H

#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include "./mlx/mlx.h"

# define WIDTH 1280
# define HEIGHT 720

//definimos numero, asi al usar la tecla la asociamos comparando estos numeros
# define W 119
# define A 97
# define S 115
# define D 100
# define ESC 65307

# define LEFT 65361
# define RIGHT 65363
# define PI 3.14159265359

# define WALL 64 //pixels

typedef struct s_player
{
    float   x;
    float   y;

    int     key_up;
    int     key_down;
    int     key_left;
    int     key_right;

    struct s_data *data;

    float   angle;
    int     left_r;
    int     right_r;

}   t_player ;

typedef struct s_data
{
    void    *mlx;
    void    *win;
    void    *img_prt;

    char    *info;
    int     bpp;
    int     line_len;
    int     endian;

    char    **map;
    t_player player;

}   t_data ;




//parsing
int     parse_args(t_data *data, char *filename);

//utils
void    ft_error(char *error_str);
void    my_pixel_put(int x, int y, int color, t_data *img);

//events
int     key_press(int keycode, t_player *player);
int     key_release(int keycode, t_player *player);
void    move_player(t_player *player);


//init
void    init_data(t_data *data);
void    init_player(t_player *player);

//render
int     draw_loop(t_data *data);
void    clean_img(t_data *data);

#endif