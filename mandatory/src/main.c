/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isegura- <isegura-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 14:04:44 by isegura-          #+#    #+#             */
/*   Updated: 2025/08/17 14:04:48 by isegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (ft_error("wrong number of arguments"), 1);
	init_data(&data);
	if (parse_args(&data, argv[1]))
	{
		cleanup_data(&data);
		return (1);
	}
	init_textures(&data);
	mlx_hook(data.win, 2, 1L << 0, key_press, &data.player);
	mlx_hook(data.win, 3, 1L << 1, key_release, &data.player);
	mlx_hook(data.win, 17, 0, handle_exit, &data);
	mlx_loop_hook(data.mlx, draw_loop, &data);
	mlx_loop(data.mlx);
	return (0);
}
