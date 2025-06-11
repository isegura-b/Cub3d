#ifndef CUB_H
#define CUB_H

#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include "./mlx/mlx.h"

# define WIDTH 1000
# define HEIGHT 1000

//definimos numero, asi al usar la tecla la asociamos comparando estos numeros
# define W 119
# define A 97
# define S 115
# define D 100
# define ESC 65307


typedef struct s_player //lo ponen en el mapa, asi que cuando hagas el gnl hay que cambiarlo
{
    float   x;
    float   y;

    int     key_up;
    int     key_down;
    int     key_left;
    int     key_right;

    struct s_data *data;

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
void    draw_square_test(int x, int y, int size, int color, t_data *data);
int     draw_loop(t_data *data);
void    clean_img(t_data *data);

#endif