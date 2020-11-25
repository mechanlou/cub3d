#include "cub.h"

static void	init_dda_vars(float window_x, t_dda_vars *dda, t_params params)
{
	dda->ray_dir[0] = params.player.ori_x + params.player.cam_x * window_x;
	dda->ray_dir[1] = params.player.ori_y + params.player.cam_y * window_x;
	dda->curr_square[0] = (int)params.player.pos_x;
	dda->curr_square[1] = (int)params.player.pos_y;
	dda->delta_dist[0] = fabs(1 / dda->ray_dir[0]);
	dda->delta_dist[1] = fabs(1 / dda->ray_dir[1]);
	if (dda->ray_dir[0] < 0)
		dda->side_dist[0] = (params.player.pos_x - dda->curr_square[0])
			* dda->delta_dist[0];
	else
		dda->side_dist[0] = (dda->curr_square[0] + 1.0 - params.player.pos_x)
			* dda->delta_dist[0];
	dda->step[0] = (dda->ray_dir[0] < 0) ? -1 : 1;
	if (dda->ray_dir[1] < 0)
		dda->side_dist[1] = (params.player.pos_y - dda->curr_square[1])
			* dda->delta_dist[1];
	else
		dda->side_dist[1] = (dda->curr_square[1] + 1.0 - params.player.pos_y)
			* dda->delta_dist[1];
	dda->step[1] = (dda->ray_dir[1] < 0) ? -1 : 1;
}

static int	check_hit(t_dda_vars *dda, t_params params, t_print_vars *vars)
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
		if (!(vars->rel_sprites_pos = cub_add_sprite_d(*dda, params, *vars)))
			return (-1);
	}
	if (params.map[dda->curr_square[1]][dda->curr_square[0]] == '1')
		return (1);
	return (0);
}

float		calc_dist(t_dda_vars dda, t_params params, t_print_vars *vars)
{
	float wall_dist;

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
	return (wall_dist);
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
	wall_dist = calc_dist(dda, params, vars);
	vars->wall_x -= floor(vars->wall_x);
	return (wall_dist);
}
