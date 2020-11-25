#include "cub.h"

/*
**	wall_spot[0] = which face (in char)
**	wall_spot[1] = x position of the ray on this wall
*/

static void	print_surfaces(int x, t_params params, t_print_vars vars)
{
	int		i;
	int		**texture;
	float	tex_spot;

	texture = cub_get_texture_infos(params, &vars);
	vars.tex_pos[0] = (int)(vars.wall_x * (float)vars.tex_size[0]);
	vars.step = (float)vars.tex_size[1] / (float)vars.line_height;
	tex_spot = (vars.start - params.window_xy[1] / 2 + vars.line_height / 2)
		* vars.step;
	i = 0;
	while (i < vars.start)
		mlx_pixel_put(params.mlx_ptr, params.win_ptr,
			x, i++, params.ceiling_rgb);
	while (i < vars.end)
	{
		vars.tex_pos[1] = (int)tex_spot;
		tex_spot += vars.step;
		mlx_pixel_put(params.mlx_ptr, params.win_ptr,
			x, i++, texture[vars.tex_pos[0]][vars.tex_pos[1]]);
	}
	while (i < params.window_xy[1])
		mlx_pixel_put(params.mlx_ptr, params.win_ptr,
			x, i++, params.floor_rgb);
}

static bool	put_line(int x, t_params params, float **buffer, t_print_vars *v)
{
	float	wall_dist;

	wall_dist = cub_cast_ray(
		2 * (float)x / params.window_xy[0] - 1, params, v);
	if (wall_dist == -1)
		return (false);
	v->line_height = (int)(params.window_xy[1] / wall_dist);
	v->start = -v->line_height / 2 + params.window_xy[1] / 2;
	if (v->start < 0)
		v->start = 0;
	v->end = v->line_height / 2 + params.window_xy[1] / 2;
	if (v->end > params.window_xy[1] || v->end < 0)
		v->end = params.window_xy[1];
	print_surfaces(x, params, *v);
	buffer[0][x] = wall_dist;
	return (true);
}

static void	sort_list(float **tab)
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

int			cub_put_map(t_params params)
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
		ret = put_line(x++, params, &buffer, &vars);
	if (ret == false)
	{
		free(buffer);
		return (-1);
	}
	sort_list(vars.rel_sprites_pos);
	cub_sprites(params, vars, buffer);
	free(buffer);
	return (0);
}
