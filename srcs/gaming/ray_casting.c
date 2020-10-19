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

static float	**add_sprite_dist(t_dda_vars dda, t_params params, t_print_vars vars)
{
	int		i;
	bool	already;
	int		size;
	float	**new_dists;
	float	new_xy[2];
	
	size = 0;
	new_xy[0] = dda.curr_square[0] - params.player.pos_x;
	new_xy[1] = dda.curr_square[1] - params.player.pos_y;
	already = false;
	while (vars.rel_sprites_pos && vars.rel_sprites_pos[size])
	{
		if (vars.rel_sprites_pos[size][0] == new_xy[0]
			&& vars.rel_sprites_pos[size][1] == new_xy[1])
			already = true;
		size++;
	}
	if (already)
		return (vars.rel_sprites_pos);
	if (!(new_dists = malloc(sizeof(float *) * (size + 2))))
		return (NULL);
	i = -1;
	while (++i < size)
		new_dists[i] = vars.rel_sprites_pos[i];
	if (!(new_dists[i] = malloc(sizeof(float) * 2)))
		return (free_tab(new_dists));
	new_dists[i][0] = new_xy[0];
	new_dists[i][1] = new_xy[1];
	new_dists[i + 1] = NULL;
	free(vars.rel_sprites_pos);
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
		if (!(vars->rel_sprites_pos = add_sprite_dist(*dda, params, *vars)))
			return (-1);
	}
	if (params.map[dda->curr_square[1]][dda->curr_square[0]] == '1')
		return (1);
	return (0);
}

float		cub_cast_ray(float window_x, t_params params, t_print_vars *vars)
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