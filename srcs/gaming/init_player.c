#include "cub.h"

static void	assign_start_ns(t_params *params, char pos)
{
	if (pos == 'N')
	{
		params->player.ori_x = 0;
		params->player.ori_y = -1;
		params->player.cam_x = FOV_SIZE;
		params->player.cam_y = 0;
	}
	else if (pos == 'S')
	{
		params->player.ori_x = 0;
		params->player.ori_y = 1;
		params->player.cam_x = -FOV_SIZE;
		params->player.cam_y = 0;
	}
}

static void	assign_start_ew(t_params *params, char pos)
{
	if (pos == 'E')
	{
		params->player.ori_x = 1;
		params->player.ori_y = 0;
		params->player.cam_x = 0;
		params->player.cam_y = FOV_SIZE;
	}
	else if (pos == 'W')
	{
		params->player.ori_x = -1;
		params->player.ori_y = 0;
		params->player.cam_x = 0;
		params->player.cam_y = -FOV_SIZE;
	}
}

void		cub_init_player(t_params *params)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (params->map[y])
	{
		x = 0;
		while (params->map[y][x])
		{
			if (ft_strchr("NSEW", params->map[y][x]))
			{
				assign_start_ns(params, params->map[y][x]);
				assign_start_ew(params, params->map[y][x]);
				params->player.pos_x = x + 0.5;
				params->player.pos_y = y + 0.5;
			}
			x++;
		}
		y++;
	}
}
