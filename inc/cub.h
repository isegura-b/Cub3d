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

enum
{
    NORTH,
    SOUTH,
    EAST,
    WEST,
} ;

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


typedef struct s_hit_info {
    float   ray_x; 
    float   ray_y;
    float   last_x; 
    float   last_y;
    int     hit_side;
    float   distance;
    float   height;
    int     start_y;
    int     end_y;
} t_hit_info;

typedef struct s_ray_vars
{
    float pos_x;
    float pos_y;
    int map_x;
    int map_y;
    float ray_dir_x;
    float ray_dir_y;
    float delta_dist_x;
    float delta_dist_y;
    float side_dist_x;
    float side_dist_y;
    int step_x;
    int step_y;
    int hit_wall;
    int side;
} t_ray_vars;

//parsing
int     parse_args(t_data *data, char *filename);

//utils
void    ft_error(char *error_str);
void    my_pixel_put(int x, int y, int color, t_data *img);
int	handle_exit(void *param);

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
int    hit_ray(int x, int y, t_data *data);

//dda
void cast_ray(t_player *player, t_data *data, float angle, t_hit_info *hit);

#endif