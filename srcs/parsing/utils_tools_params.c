#include "cub.h"

void	cub_free_params(t_params params)
{
	free(params.path_sprite);
	free(params.path_no);
	free(params.path_so);
	free(params.path_we);
	free(params.path_ea);
	cub_free_tab((void **)params.map, 0);
	cub_free_tab((void **)params.textures.north, 0);
	cub_free_tab((void **)params.textures.south, 0);
	cub_free_tab((void **)params.textures.east, 0);
	cub_free_tab((void **)params.textures.west, 0);
	cub_free_tab((void **)params.textures.sprite, 0);
	mlx_destroy_window(params.mlx_ptr, params.win_ptr);
}

int		cub_prep_tool_param(t_pars_tool *check, t_params *params)
{
	if (!(params->mlx_ptr = mlx_init()))
		return (EXIT_FAILURE);
	check->window = false;
	check->ceiling = false;
	check->floor = false;
	check->map_start = false;
	check->map_end = false;
	params->path_ea = NULL;
	params->path_no = NULL;
	params->path_we = NULL;
	params->path_so = NULL;
	params->path_sprite = NULL;
	params->textures.north = NULL;
	params->textures.south = NULL;
	params->textures.east = NULL;
	params->textures.west = NULL;
	params->textures.sprite = NULL;
	params->ceiling_rgb = 0;
	params->floor_rgb = 0;
	params->window_xy[0] = 0;
	params->window_xy[1] = 0;
	if (!(params->map = malloc(sizeof(char *))))
		return (-1);
	params->map[0] = NULL;
	return (true);
}

/*
** checks if we have all the params (except map)
*/

bool	cub_check_all_tools(t_pars_tool to_check, t_params params)
{
	if (!to_check.window || !to_check.ceiling || !to_check.floor
	|| !params.path_ea || !params.path_we || !params.path_no
	|| !params.path_sprite || !params.path_so)
		return (false);
	return (true);
}

int		cub_free_all(const int number, ...)
{
	va_list	params;
	int		i;
	char	*str;

	i = 0;
	va_start(params, number);
	while (i < number)
	{
		str = va_arg(params, char*);
		if (str)
			free(str);
		i++;
	}
	va_end(params);
	return (-1);
}
