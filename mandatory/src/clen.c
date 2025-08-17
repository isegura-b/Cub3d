/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clen.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isegura- <isegura-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 14:00:53 by isegura-          #+#    #+#             */
/*   Updated: 2025/08/17 15:12:20 by isegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	cleanup_textures(t_data *data)
{
	if (data->info_file.no)
		free(data->info_file.no);
	if (data->info_file.so)
		free(data->info_file.so);
	if (data->info_file.ea)
		free(data->info_file.ea);
	if (data->info_file.we)
		free(data->info_file.we);
}

void	cleanup_data(t_data *data)
{
	int	i;

	i = 0;
	if (data->info_file.map)
	{
		while (data->info_file.map[i])
		{
			free(data->info_file.map[i]);
			i++;
		}
		free(data->info_file.map);
	}
	if (data->img_prt)
		mlx_destroy_image(data->mlx, data->img_prt);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
}
