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

static int	check_hit(t_dda_vars *dda, t_params params)
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
	// dprintf(1, "%d %d\n%c\n", dda->curr_square[1], dda->curr_square[0], params.map[dda->curr_square[1]][dda->curr_square[0]]);
	if (params.map[dda->curr_square[1]][dda->curr_square[0]] == '1')
		return (1);
	return (0);
}

static float	cast_ray(float window_x, t_params params)
{
	t_dda_vars	dda;
	int			hit;
	float		wall_dist;

	init_dda_vars(window_x, &dda, params);
	hit = 0;
	while (hit == 0)
		hit = check_hit(&dda, params);
	if (dda.side == 0)
		wall_dist = (dda.curr_square[0] - params.player.pos_x +
		(1 - dda.step[0]) / 2) / dda.ray_dir[0];
	else 
		wall_dist = (dda.curr_square[1] - params.player.pos_y +
		(1 - dda.step[1]) / 2) / dda.ray_dir[1];
	dprintf(1, "------------\nwall_dist %f\nori   %f\n", wall_dist, (atan2(dda.ray_dir[0], dda.ray_dir[1]))/(2 * 3.14159265) * 360);
	// dprintf(1, "curr  %d %d\n", dda.curr_square[0], dda.curr_square[1]);
	return (wall_dist);
}

static void	put_line(int x, t_params params)
{
	int		line_height;
	float	wall_dist;
	int		i;
	int		start;
	int		end;

	wall_dist = cast_ray(2 * (float)x / params.window_xy[0] - 1, params);
	line_height = (int)(params.window_xy[1] / wall_dist);
	start = -line_height / 2 + params.window_xy[1] / 2;
	if (start < 0)
		start = 0;
	end = line_height / 2 + params.window_xy[1] / 2;
	if (end > params.window_xy[1] || end < 0)
		end = params.window_xy[1];
	i = 0;
	while (i < start)
		mlx_pixel_put(params.mlx_ptr, params.win_ptr, x, i++, params.ceiling_rgb);
	while (i < end)
		mlx_pixel_put(params.mlx_ptr, params.win_ptr, x, i++, 16725248);
	while (i < params.window_xy[1])
		mlx_pixel_put(params.mlx_ptr, params.win_ptr, x, i++, params.floor_rgb);
}

int			cub_put_map(t_params params)
{
	int	x;

	x = 0;
	while (x < params.window_xy[0])
		put_line(x++, params);
	dprintf(1, "\n");
	return (0);
}