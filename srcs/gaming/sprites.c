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
	while (params.textures.sprite[vars->tex_size[0] - 1][vars->tex_size[1]] > -1)
		vars->tex_size[1]++;
	i = 0;
	while (vars->rel_sprites_pos && vars->rel_sprites_pos[i])
		i++;
	i--;
	return (i);
}

void			cub_print_sprites(t_params params, t_print_vars vars, float *line_buff)
{
	int		i;
	int		xy[2];
	int		sprite_screen_x;
	int		sprite_size;
	float	inv_det;
	int 	start_end[2][2];
	float	transform[2];

	i = init_sprites_infos(params, &vars);
	while (i >= 0)
	{
		inv_det = 1.0 / (params.player.cam_x * params.player.ori_y - params.player.ori_x * params.player.cam_y);
		transform[0] = inv_det * (params.player.ori_y * vars.rel_sprites_pos[i][0] - params.player.ori_x * vars.rel_sprites_pos[i][1]);
		transform[1] = inv_det * (-params.player.cam_y * vars.rel_sprites_pos[i][0] + params.player.cam_x * vars.rel_sprites_pos[i][1]);
		sprite_screen_x = (int)(params.window_xy[0] / 2) *  (1 + transform[0] / transform[1]);
		sprite_size = abs((int)(params.window_xy[1] / transform[1]));
		dprintf(1, "sprite_size %d\n", sprite_size);
		start_end[0][1] = -sprite_size / 2 + params.window_xy[1] / 2;
		start_end[0][1] = (start_end[0] < 0) ? 0 : start_end[0][1];
		start_end[1][1] = sprite_size / 2 + params.window_xy[1] / 2;
		if (start_end[1][1] >= params.window_xy[1])
			start_end[1][1] = params.window_xy[1] - 1;
		start_end[0][0] = -sprite_size / 2 + sprite_screen_x;
		if (start_end[0][0] < 0)
			start_end[0][0] = 0;
		start_end[1][0] = sprite_size / 2 + sprite_screen_x;
		if (start_end[1][0] >= params.window_xy[0])
			start_end[1][0] = params.window_xy[0] - 1;
		dprintf(1, "start_endx %d %d\n", start_end[0][0], start_end[1][0]);
		xy[0] = start_end[0][0];
		while (xy[0] < start_end[1][0])
		{
			vars.tex_pos[0] = (int)(256 * (xy[0] - (-sprite_size / 2 + sprite_screen_x)) * vars.tex_size[0] / sprite_size) / 256;
			if (transform[1] > 0 && xy[0] > 0 && xy[0] < params.window_xy[0] && transform[1] < line_buff[xy[0]])
			{
				xy[1] = start_end[0][1];
				while (xy[1] < start_end[1][1])
				{
					vars.tex_pos[1] = (xy[1] - params.window_xy[1] + sprite_size * (vars.tex_size[1] - 1)) / sprite_size;
					dprintf(1, "tex_pos %d %d\n", vars.tex_pos[0], vars.tex_pos[1]);
					if (params.textures.sprite[vars.tex_pos[0]][vars.tex_pos[1]] != 0)
						mlx_pixel_put(params.mlx_ptr, params.win_ptr, xy[0], xy[1]++, params.textures.sprite[vars.tex_pos[0]][vars.tex_pos[1]]);
				}
			}
			xy[0]++;
		}
		i--;
		write(1, "\n", 1);
	}
	free_tab(vars.rel_sprites_pos);
}
