#include "cub.h"

static float	**free_tab(float **tab)
{
	int i;
	
	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (NULL);
}

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

static int		all_sprites_calc(t_params params, t_print_vars *vars, int i)
{
	float	inv_det;
	int		sprite_size;

	inv_det = 1.0 / (params.player.cam_x * params.player.ori_y
		- params.player.ori_x * params.player.cam_y);
	vars->transform[0] = inv_det * (params.player.ori_y * vars->rel_sprites_pos
		[i][0] - params.player.ori_x * vars->rel_sprites_pos[i][1]);
	vars->transform[1] = inv_det * (-params.player.cam_y
		* vars->rel_sprites_pos[i][0] + params.player.cam_x
		* vars->rel_sprites_pos[i][1]);
	vars->sprite_screen_x = (int)(params.window_xy[0] / 2)
		* (1 + vars->transform[0] / vars->transform[1]);
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

static void		s_print(t_print_vars v, t_params p, float *l_buff, t_image *i)
{
	int y;
	int x;

	x = v.start_end[0][0];
	while (x < v.start_end[1][0])
	{
		v.tex_pos[0] = (int)(256 * (x - (-v.sprite_size / 2 +
			v.sprite_screen_x)) * v.tex_size[0] / v.sprite_size) / 256;
		if (v.transform[1] > 0 && x > 0 && x < p.window_xy[0]
			&& v.transform[1] < l_buff[x])
		{
			y = v.start_end[0][1];
			while (y < v.start_end[1][1])
			{
				v.tex_pos[1] = (((y * 256 - p.window_xy[1] * 128 +
				v.sprite_size * 128) * v.tex_size[1]) / v.sprite_size) / 256;
				if (p.textures.sprite[v.tex_pos[0]][v.tex_pos[1]] != 0)
					cub_pixel_to_image(i, x, y,
						p.textures.sprite[v.tex_pos[0]][v.tex_pos[1]]);
				y++;
			}
		}
		x++;
	}
}

void			cub_scr_spr(t_params p, t_print_vars v, float *l_b, t_image *i)
{
	int		j;

	j = init_sprites_infos(p, &v);
	while (j >= 0)
	{
		v.sprite_size = all_sprites_calc(p, &v, j);
		s_print(v, p, l_b, i);
		j--;
	}
	free_tab(v.rel_sprites_pos);
}