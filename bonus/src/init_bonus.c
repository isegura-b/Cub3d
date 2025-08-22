/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hellkid <hellkid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:00:00 by hellkid          #+#    #+#             */
/*   Updated: 2025/08/17 14:01:31 by isegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	load_texture(t_data *data, t_texture *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(data->mlx, path, &tex->width,
			&tex->height);
	if (!tex->img)
	{
		printf("Error: Texture could not be loaded: %s\n", path);
		exit(EXIT_FAILURE);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len,
			&tex->endian);
	if (!tex->addr)
	{
		printf("Error: Coudn't find texture: %s\n", path);
		exit(EXIT_FAILURE);
	}
}

void	init_player(t_player *player)
{
	player->key_up = 0;
	player->key_down = 0;
	player->key_left = 0;
	player->key_right = 0;
	player->left_r = 0;
	player->right_r = 0;
}

void	init_info_file(t_info_file *info_file)
{
	info_file->no = NULL;
	info_file->so = NULL;
	info_file->ea = NULL;
	info_file->we = NULL;
	info_file->floor = -1;
	info_file->sky = -1;
	info_file->map = NULL;
	info_file->map_width = 0;
	info_file->map_hight = 0;
	info_file->player_x = 0;
	info_file->player_y = 0;
	info_file->player_angle = 0;
}

void	init_data(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3D");
	data->img_prt = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->info = mlx_get_data_addr(data->img_prt, &data->bpp, &data->line_len,
			&data->endian);
	data->player.data = data;
	init_player(&data->player);
}

void	init_textures(t_data *data)
{
	if (!data->info_file.no || !data->info_file.so || !data->info_file.ea
		|| !data->info_file.we)
		ft_error("Texture missing in the .cub file");
	load_texture(data, &data->textures[NORTH], data->info_file.no);
	load_texture(data, &data->textures[SOUTH], data->info_file.so);
	load_texture(data, &data->textures[EAST], data->info_file.ea);
	load_texture(data, &data->textures[WEST], data->info_file.we);
}
