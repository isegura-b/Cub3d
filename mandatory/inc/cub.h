/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isegura- <isegura-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:47:23 by isegura-          #+#    #+#             */
/*   Updated: 2025/08/26 21:08:23 by isegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "./get_next_line.h"
# include "../../inc/mlx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 1280
# define HEIGHT 720

// definimos numero, asi al usar la tecla la asociamos comparando estos numeros
# define W 119
# define A 97
# define S 115
# define D 100
# define ESC 65307

# define LEFT 65361
# define RIGHT 65363
# define PI 3.14159265359

# define WALL 64 // pixels

enum
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
};

typedef struct s_info_file
{
	// is texture
	char			*no;
	char			*so;
	char			*ea;
	char			*we;
	// is color
	int				floor;
	int				sky;
	// map
	char			**map;
	int				map_width;
	int				map_hight;
	int				player_x;
	int				player_y;
	float			player_angle;
}					t_info_file;

typedef struct s_texture
{
	void			*img;
	char			*addr;
	int				width;
	int				height;
	int				bpp;
	int				line_len;
	int				endian;
}					t_texture;

typedef struct s_player
{
	float			x;
	float			y;

	int				key_up;
	int				key_down;
	int				key_left;
	int				key_right;

	struct s_data	*data;

	float			angle;
	int				left_r;
	int				right_r;

}					t_player;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	void			*img_prt;

	char			*info;
	int				bpp;
	int				line_len;
	int				endian;

	char			**map;
	t_player		player;
	t_texture		textures[4];
	t_info_file		info_file;

}					t_data;

typedef struct s_hit_info
{
	float			ray_x;
	float			ray_y;
	float			last_x;
	float			last_y;
	int				hit_side;
	float			distance;
	float			height;
	int				start_y;
	int				end_y;
}					t_hit_info;

typedef struct s_ray_vars
{
	float			pos_x;
	float			pos_y;
	int				map_x;
	int				map_y;
	float			ray_dir_x;
	float			ray_dir_y;
	float			delta_dist_x;
	float			delta_dist_y;
	float			side_dist_x;
	float			side_dist_y;
	int				step_x;
	int				step_y;
	int				hit_wall;
	int				side;
}					t_ray_vars;

typedef struct s_wall_info
{
	t_hit_info		*hit;
	int				x;
	t_texture		*tex;
	int				tex_x;
	t_data			*data;
}					t_wall_info;

typedef struct s_wall_calc
{
	int				wall_height;
	int				y;
	int				d;
	int				tex_y;
	int				color;
}					t_wall_calc;

typedef struct s_mapinfo
{
	char			**map;
	int				width;
	int				height;
}					t_mapinfo;

typedef struct s_point
{
	int				x;
	int				y;
}					t_point;

// parsing
int					parse_args(t_data *data, char *filename);

// utils
void				ft_error(char *error_str);
void				my_pixel_put(int x, int y, int color, t_data *img);
int					handle_exit(void *param);
char				*ft_strdup(const char *s);
char				*ft_strdup_path(const char *s);

// events
int					key_press(int keycode, t_player *player);
int					key_release(int keycode, t_player *player);
int					mouse_move(int x, int y, t_data *data);
void				move_player(t_player *player);

// init
void				init_data(t_data *data);
void				init_player(t_player *player);
void				load_texture(t_data *data, t_texture *tex, char *path);
void				init_info_file(t_info_file *info_file);
void				init_textures(t_data *data);
void				cleanup_data(t_data *data);

// render
void				clean_img(t_data *data);
int					hit_ray(int x, int y, t_data *data);
int					get_tex_pixel(t_texture *tex, int x, int y);
void				draw_wall(t_player *player, t_data *data, float angle,
						int i);
int					draw_loop(t_data *data);

// dda
void				perform_dda(t_ray_vars *var, t_data *data);
void				calculate_hit_info(t_hit_info *hit, t_ray_vars *var);
void				init_ray_steps(t_ray_vars *var);
void				init_ray_vars(t_ray_vars *var, t_player *player,
						float angle);
void				cast_ray(t_player *player, t_data *data, float angle,
						t_hit_info *hit);

// render_tex
void				draw_column(t_hit_info *hit, int i, t_data *data);
float				get_wall_hit_x(t_hit_info *hit);
int					get_tex_x(float wall_x, int side, t_texture *tex,
						t_hit_info *hit);
void				draw_sky(int x, int end_y, t_data *data);
void				draw_floor(int x, int start_y, t_data *data);
void				draw_tex_wall(t_wall_info *w);

// path file info
int					is_empty_line(const char *line);
int					is_texture(char *line);
int					is_color(char *line);
int					is_map_line(char *line);

// save_info files
void				info_texture(char *line, t_info_file *info_file);
int					rgb_to_int(const char *str);
void				info_colors(char *line, t_info_file *info_file);
int					ft_map(char *line, t_info_file *info_file);
int					find_player_position(t_data *data);

// gnl
char				*get_next_line(int fd);

// gnl_utils
void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_strjoin(char *s1, char *s2);
size_t				ft_strlen(const char *s);
char				*ft_strchr(const char *s, int c);

void				draw_minimap(t_data *data);

size_t				ft_maplen(const char *s);
int					get_step(const t_player *p, float *dx, float *dy);

// utils2

int					get_step(const t_player *p, float *dx, float *dy);
int					get_dir(const t_player *p, float *dx, float *dy);
void				normalize_angle(t_player *p);
float				dir_angle(char c);
char				**copy_map(char **map, int height, int width);
int					is_cub_file(char *filename);
int					parse_file(t_data *data, char *filename);
int					is_invalid_char(char c);
void				free_map(char **map, int height);
int					check_map(t_data *data, char *filename);
int					error_close(int fd, char *line);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					normalize_map(t_info_file *info);
void				free_map(char **map, int height);
int					is_invalid_char(char c);
int					parse_file(t_data *data, char *filename);

#endif
