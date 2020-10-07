#include "cub.h"

static void		init_dda_vars(float window_x, t_dda_vars *dda, t_params params)
{
	dda->ray_dir[0] = params.player.ori_x + params.player.cam_x * window_x;
	dda->ray_dir[1] = params.player.ori_y + params.player.cam_y * window_x;
	dda->curr_square[0] = (int)params.player.pos_x;
	dda->curr_square[1] = (int)params.player.pos_y;
	dda->delta_dist[0] = fabs(1 / dda->ray_dir[0]);
	dda->delta_dist[1] = fabs(1 / dda->ray_dir[1]);
	if (dda->ray_dir[0] < 0)
		dda->side_dist[0] = (params.player.pos_x - dda->curr_square[0]) * dda->delta_dist[0];
	else
		dda->side_dist[0] = (dda->curr_square[0] + 1.0 - params.player.pos_x) * dda->delta_dist[0];
	dda->step[0] = (dda->ray_dir[0] < 0) ? -1 : 1;
	if (dda->ray_dir[1] < 0)
		dda->side_dist[1] = (params.player.pos_y - dda->curr_square[1]) * dda->delta_dist[1];
	else
		dda->side_dist[1] = (dda->curr_square[1] + 1.0 - params.player.pos_y) * dda->delta_dist[1];
	dda->step[1] = (dda->ray_dir[1] < 0) ? -1 : 1;
}

static float	**free_tab(float **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
			free(tab[i++]);
		free(tab);
	}
	return (NULL);
}

static float	**add_dist(t_dda_vars dda, t_params params, t_print_vars vars)
{
	int		i;
	float	**new_dists;
	
	i = 0;
	while (vars.sprites_dist && vars.sprites_dist[i])
		i++;
	if (!(new_dists = malloc(sizeof(float *) * (i + 2))))
		return (NULL);
	if (!(new_dists[i] = malloc(sizeof(float) * 2)))
		return (free_tab(new_dists));
	new_dists[i + 1] = NULL;
	new_dists[i][0] = (float)fabs(sqrtf(
		(dda.curr_square[0] + 0.5 - params.player.pos_x)
		* (dda.curr_square[0] + 0.5 - params.player.pos_x)
		+ (dda.curr_square[1]  + 0.5 - params.player.pos_y)
		* (dda.curr_square[1] +0.5 - params.player.pos_y)));
	new_dists[i][1] = params.player.pos_x + new_dists[i][0] * dda.ray_dir[0];
	new_dists[i][1] -=floor(new_dists[i][1]);
	i--;
	while (i >= 0)
	{
		new_dists[i] = vars.sprites_dist[i];
		i--;
	}
	free(vars.sprites_dist);
	return (new_dists);
}

static int		check_hit(t_dda_vars *dda, t_params params, t_print_vars *vars)
{
	if (dda->side_dist[0] < dda->side_dist[1])
	{
		dda->side_dist[0] += dda->delta_dist[0];
		dda->curr_square[0] += dda->step[0];
		dda->side = 0;
	}
	else
	{
		dda->side_dist[1] += dda->delta_dist[1];
		dda->curr_square[1] += dda->step[1];
		dda->side = 1;
	}
	if (params.map[dda->curr_square[1]][dda->curr_square[0]] == '2')
	{
		if (!(vars->sprites_dist = add_dist(*dda, params, *vars)))
			return (-1);
	}
	if (params.map[dda->curr_square[1]][dda->curr_square[0]] == '1')
		return (1);
	return (0);
}

static float	cast_ray(float window_x, t_params params, t_print_vars *vars)
{
	t_dda_vars	dda;
	int			hit;
	float		wall_dist;

	init_dda_vars(window_x, &dda, params);
	hit = 0;
	while (hit == 0)
		hit = check_hit(&dda, params, vars);
	if (hit == -1)
		return (-1);
	if (dda.side == 0)
	{
		wall_dist = (dda.curr_square[0] - params.player.pos_x +
			(1 - dda.step[0]) / 2) / dda.ray_dir[0];
		vars->face = (dda.ray_dir[0] < 0) ? 'W' : 'E';
		vars->wall_x = params.player.pos_y + wall_dist * dda.ray_dir[1];
	}
	else
	{
		wall_dist = (dda.curr_square[1] - params.player.pos_y +
			(1 - dda.step[1]) / 2) / dda.ray_dir[1];
		vars->face = (dda.ray_dir[1] < 0) ? 'N' : 'S';
		vars->wall_x = params.player.pos_x + wall_dist * dda.ray_dir[0];
	}
	vars->wall_x -= floor(vars->wall_x);
	return (wall_dist);
}
	// dprintf(1, "------------\nwall_dist %f\nori   %f\n", wall_dist, (atan2(dda.ray_dir[0], dda.ray_dir[1]))/(2 * 3.14159265) * 360);
	// dprintf(1, "curr  %d %d\n", dda.curr_square[0], dda.curr_square[1]);

/*
**	wall_spot[0] = which face (in char)
**	wall_spot[1] = x position of the ray on this wall
*/

static int	**get_texture_infos(t_params params, t_print_vars *vars)
{
	int		**texture;

	if (vars->face == 'N')
		texture = params.textures.north;
	else if (vars->face == 'S')
		texture = params.textures.south;
	else if (vars->face == 'E')
		texture = params.textures.east;
	else
		texture = params.textures.west;
	vars->tex_size[0] = 0;
	vars->tex_size[1] = 0;
	while (texture[vars->tex_size[0]])
		vars->tex_size[0]++;
	while (texture[vars->tex_size[0] - 1][vars->tex_size[1]] > -1)
		vars->tex_size[1]++;
	return (texture);
}

static void	print_sprites(t_params params, t_print_vars vars)
{
	int i;
	int	**texture;

	texture = get_texture_infos(params, &vars);
	i = 0;
	while (vars.sprites_dist && vars.sprites_dist[i])
	{
		dprintf(1, "%f", vars.sprites_dist[i++][0]);
		write(1, "\n", 1);
	}
}

static void print_line(int x, t_params params, t_print_vars vars)
{
	int		i;
	int		**texture;
	float	tex_spot;

	texture = get_texture_infos(params, &vars);
	vars.tex_pos[0] = (int)(vars.wall_x * (float)vars.tex_size[0]);
	// if (vars.face == 'W' || vars.face == 'S')
	// 	vars.tex_pos[0] = vars.tex_size[0] - vars.tex_pos[0] - 1;
	vars.step = (float)vars.tex_size[1] / (float)vars.line_height;
	tex_spot = (vars.start - params.window_xy[1] / 2 + vars.line_height / 2) * vars.step;
	i = 0;
	while (i < vars.start)
		mlx_pixel_put(params.mlx_ptr, params.win_ptr, x, i++, params.ceiling_rgb);
	while (i < vars.end)
	{
		vars.tex_pos[1] = (int)tex_spot & (vars.tex_size[0] - 1);
		tex_spot += vars.step;
		mlx_pixel_put(params.mlx_ptr, params.win_ptr, x, i++, texture[vars.tex_pos[0]][vars.tex_pos[1]]);
	}
	while (i < params.window_xy[1])
		mlx_pixel_put(params.mlx_ptr, params.win_ptr, x, i++, params.floor_rgb);
}

static bool	put_line(int x, t_params params)
{
	float			wall_dist;
	t_print_vars	vars;

	vars.sprites_dist = NULL;
	wall_dist = cast_ray(2 * (float)x / params.window_xy[0] - 1, params, &vars);
	if (wall_dist == -1)
		return (false);
	vars.line_height = (int)(params.window_xy[1] / wall_dist);
	vars.start = -vars.line_height / 2 + params.window_xy[1] / 2;
	if (vars.start < 0)
		vars.start = 0;
	vars.end = vars.line_height / 2 + params.window_xy[1] / 2;
	if (vars.end > params.window_xy[1] || vars.end < 0)
		vars.end = params.window_xy[1];
	print_line(x, params, vars);
	print_sprites(params, vars);
	return (true);
}

int			cub_put_map(t_params params)
{
	int		x;
	bool	ret;

	x = 0;
	ret = true;
	while (x < params.window_xy[0] && ret == true)
		ret = put_line(x++, params);
	if (ret == false)
		return (-1);
	return (0);
}