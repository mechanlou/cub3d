#include "cub.h"

static void		sort_list(float **tab)
{
	int		i;
	float	dist[2];
	float	temp[2];

	if (tab && tab[0])
	{
		i = 0;
		while (tab[i + 1])
		{
			dist[0] = sqrt(tab[i][0] * tab[i][0] + tab[i][1] * tab[i][1]);
			dist[1] = sqrt(tab[i + 1][0] * tab[i + 1][0]
				+ tab[i + 1][1] * tab[i + 1][1]);
			if (dist[0] > dist[1])
			{
				temp[0] = tab[i][0];
				temp[1] = tab[i][1];
				tab[i][0] = tab[i + 1][0];
				tab[i][1] = tab[i + 1][1];
				tab[i + 1][0] = temp[0];
				tab[i + 1][1] = temp[1];
				i = -1;
			}
			i++;
		}
		
	}
}

static int		show_screenshot(t_params params, t_image *image)
{
	int				x;
	t_print_vars	vars;
	bool			ret;
	float			*buffer;

	if (!(buffer = (float *)malloc(sizeof(float) * params.window_xy[0])))
		return (-1);
	vars.rel_sprites_pos = NULL;
	x = 0;
	ret = true;
	while (x < params.window_xy[0] && ret == true)
	{
		ret = cub_sc_l(params, &buffer, &vars, image);
		vars.sprite_size = x++;
	}
	if (ret == false)
	{
		free(buffer);
		return (-1);
	}
	sort_list(vars.rel_sprites_pos);
	cub_scr_spr(params, vars, buffer, image);
	free(buffer);
	return (0);
}

void			cub_take_screenshot(t_params params)
{
	t_image	image;

	image.image = mlx_new_image(params.mlx_ptr, params.window_xy[0],
		params.window_xy[1]);
	image.data = mlx_get_data_addr(image.image, &image.bpp, &image.line_size,
		&image.endian);
	if (show_screenshot(params, &image))
	{
		cub_free_params(params);
		dprintf(1, "Error\n%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	cub_save_bmp(params, image);
	mlx_destroy_image(params.mlx_ptr, image.image);
}
