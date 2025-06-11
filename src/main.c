#include "../inc/cub.h"   


int	handle_exit(void *param)
{
	t_data *data = (t_data *)param;

	mlx_destroy_window(data->mlx, data->win);
	exit(0);
	return (0);
}

int main(int argc, char **argv)
{
    t_data data;  //missing

    if (argc != 2)
        return (ft_error("wrong number of arguments"), 1);
    init_data(&data);
    //if(parse_args(&data, argv[1]))
    //    return(1);
    mlx_hook(data.win, 2, 1L << 0, key_press, &data);
    mlx_hook(data.win, 3, 1L << 1, key_release, &data.player);
    mlx_hook(data.win, 17, 0, handle_exit, &data);

    mlx_loop_hook(data.mlx, draw_loop, &data);
    mlx_loop(data.mlx);
    
    return (0);
}