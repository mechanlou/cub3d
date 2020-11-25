#include "cub.h"

static int		init_sprites_infos(t_params params, t_print_vars *vars)
{
	int i;

	vars->tex_size[1] = 0;
	vars->tex_size[0] = 0;
	while (params.textures.sprite[vars->tex_size[0]])
		vars->tex_size[0]++;
	while (params.textures.sprite[vars->tex_size[0] - 1][vars->tex_size[1]]
			!= -2147483648)
		vars->tex_size[1]++;
	i = 0;
	while (vars->rel_sprites_pos && vars->rel_sprites_pos[i])
		i++;
	i--;
	return (i);
}

/*
**	start_end[a][b] --> a à 0 = start / 1 = end;  b à 0 = x / 1 = y;
*/

static void		sprites_calc_bis(t_params params, t_print_vars *vars, int i)
{
	float	inv_det;

	inv_det = 1.0 / (params.player.cam_x * params.player.ori_y
		- params.player.ori_x * params.player.cam_y);
	vars->transform[0] = inv_det * (params.player.ori_y * vars->rel_sprites_pos
		[i][0] - params.player.ori_x * vars->rel_sprites_pos[i][1]);
	vars->transform[1] = inv_det * (-params.player.cam_y
		* vars->rel_sprites_pos[i][0] + params.player.cam_x
		* vars->rel_sprites_pos[i][1]);
	vars->sprite_screen_x = (int)(params.window_xy[0] / 2)
		* (1 + vars->transform[0] / vars->transform[1]);
}

static int		all_sprites_calc(t_params params, t_print_vars *vars, int i)
{
	int		sprite_size;

	sprites_calc_bis(params, vars, i);
	sprite_size = abs((int)(params.window_xy[1] / vars->transform[1]));
	vars->start_end[0][1] = -sprite_size / 2 + params.window_xy[1] / 2;
	vars->start_end[0][1] = (vars->start_end[0] < 0)
		? 0 : vars->start_end[0][1];
	vars->start_end[1][1] = sprite_size / 2 + params.window_xy[1] / 2;
	if (vars->start_end[1][1] >= params.window_xy[1])
		vars->start_end[1][1] = params.window_xy[1] - 1;
	vars->start_end[0][0] = -sprite_size / 2 + vars->sprite_screen_x;
	if (vars->start_end[0][0] < 0)
		vars->start_end[0][0] = 0;
	vars->start_end[1][0] = sprite_size / 2 + vars->sprite_screen_x;
	if (vars->start_end[1][0] >= params.window_xy[0])
		vars->start_end[1][0] = params.window_xy[0] - 1;
	return (sprite_size);
}

static void		s_print(t_print_vars v, t_params p, int s_size, float *l_buff)
{
	int y;
	int x;

	x = v.start_end[0][0];
	while (x < v.start_end[1][0])
	{
		v.tex_pos[0] = (int)(256 * (x - (-s_size / 2 + v.sprite_screen_x))
			* v.tex_size[0] / s_size) / 256;
		if (v.transform[1] > 0 && x > 0 && x < p.window_xy[0]
			&& v.transform[1] < l_buff[x])
		{
			y = v.start_end[0][1];
			while (y < v.start_end[1][1])
			{
				v.tex_pos[1] = (((y * 256 - p.window_xy[1] * 128 + s_size
					* 128) * v.tex_size[1]) / s_size) / 256;
				if (p.textures.sprite[v.tex_pos[0]][v.tex_pos[1]] != 0)
					mlx_pixel_put(p.mlx_ptr, p.win_ptr, x, y,
						p.textures.sprite[v.tex_pos[0]][v.tex_pos[1]]);
				y++;
			}
		}
		x++;
	}
}

void			cub_sprites(t_params params, t_print_vars vars, float *l_buff)
{
	int		i;
	int		sprite_size;

	i = init_sprites_infos(params, &vars);
	while (i >= 0)
	{
		sprite_size = all_sprites_calc(params, &vars, i);
		s_print(vars, params, sprite_size, l_buff);
		i--;
	}
	cub_free_ftab(vars.rel_sprites_pos);
}
