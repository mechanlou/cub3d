#include "cub.h"

static void	error_case(t_params params, char *error)
{
	cub_free_params(params);
	dprintf(1, "Error\n%s\n", error);
	exit(EXIT_FAILURE);
}

void		cub_the_game(t_params params, int argc)
{
	cub_check_screen_size(&params);
	cub_init_player(&params);
	if (!(cub_init_textures(&params)))
		error_case(params, strerror(errno));
	if (argc == 3)
	{
		cub_take_screenshot(params);
		write(1, "Cheese !  *click*\n", 18);
	}
	else
	{
		if (!(params.win_ptr = mlx_new_window(params.mlx_ptr,
			params.window_xy[0], params.window_xy[1], "cub3D")))
			error_case(params, "It's broken");
		mlx_do_key_autorepeaton(params.mlx_ptr);
		if (cub_put_map(params) == -1)
			error_case(params, strerror(errno));
		mlx_hook(params.win_ptr, 2, 1L << 0, &cub_key_press_hook, &params);
		mlx_hook(params.win_ptr, 3, 1L << 1, &cub_key_release_hook, &params);
		mlx_loop(params.mlx_ptr);
	}
}