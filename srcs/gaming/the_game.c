#include "cub.h"

static void assign_start_NS(t_params *params, char pos)
{
	if (pos == 'N')
	{
		params->player.ori_x = 0;
		params->player.ori_y = -1;
		params->player.cam_x = FOV_SIZE;
		params->player.cam_y = 0;
	}
	else if (pos == 'S')
	{
		params->player.ori_x = 0;
		params->player.ori_y = 1;
		params->player.cam_x = -FOV_SIZE;
		params->player.cam_y = 0;
	}
}

static void assign_start_EW(t_params *params, char pos)
{
	if (pos == 'E')
	{
		params->player.ori_x = 1;
		params->player.ori_y = 0;
		params->player.cam_x = 0;
		params->player.cam_y = FOV_SIZE;
	}
	else if (pos == 'W')
	{
		params->player.ori_x = -1;
		params->player.ori_y = 0;
		params->player.cam_x = 0;
		params->player.cam_y = -FOV_SIZE;
	}
}

static void	init_player(t_params *params)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (params->map[y])
	{
		x = 0;
		while (params->map[y][x])
		{
			if (ft_strchr("NSEW", params->map[y][x]))
			{
				assign_start_NS(params, params->map[y][x]);
				assign_start_EW(params, params->map[y][x]);
				params->player.pos_x = x + 0.5;
				params->player.pos_y = y + 0.5;
			}
			x++;
		}
		y++;		
	}
}

/*static int	close_window(t_params *params)
{
	cub_free_params(*params);
	exit(EXIT_SUCCESS);
	return (0);
}*/

void		cub_the_game(t_params params, int argc)
{
	if (argc == 3)
		dprintf(1, "mdr je sais pas faire les screenshots\n");
	else
	{
		if (!(params.win_ptr = mlx_new_window(params.mlx_ptr, params.window_xy[0],
		params.window_xy[1], "test ta race nan ?")))
		{
			cub_free_params(params);
			exit(EXIT_FAILURE);
		}
		init_player(&params);
		cub_put_map(params);
		mlx_hook(params.win_ptr, 2, 1L << 0, &cub_key_press_hook, &params);
		mlx_hook(params.win_ptr, 3, 1L << 1, &cub_key_release_hook, &params);
		mlx_loop(params.mlx_ptr);
	}
}