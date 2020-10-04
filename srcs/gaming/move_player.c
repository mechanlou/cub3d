#include "cub.h"

static void go_forward(t_params *params)
{
	char new_block;

	new_block = params->map[(int)params->player.pos_y]
		[(int)(params->player.pos_x + params->player.ori_x * MOVE_SPEED)];
	if (new_block != '1')	
		params->player.pos_x += params->player.ori_x * MOVE_SPEED;
	new_block = params->map[(int)(params->player.pos_y
		+ params->player.ori_y * MOVE_SPEED)][(int)params->player.pos_x];
	if (new_block != '1')	
		params->player.pos_y += params->player.ori_y * MOVE_SPEED;
}

static void	go_backward(t_params *params)
{
	char new_block;

	new_block = params->map[(int)params->player.pos_y]
		[(int)(params->player.pos_x - params->player.ori_x * MOVE_SPEED)];
	if (new_block != '1')	
		params->player.pos_x -= params->player.ori_x * MOVE_SPEED;
	new_block = params->map[(int)(params->player.pos_y
		- params->player.ori_y * MOVE_SPEED)][(int)params->player.pos_x];
	if (new_block != '1')	
		params->player.pos_y -= params->player.ori_y * MOVE_SPEED;
}

static void go_right(float *side_vector, t_params *params)
{
	char 	new_block;

	new_block = params->map[(int)params->player.pos_y]
		[(int)(params->player.pos_x + side_vector[0] * MOVE_SPEED)];
	if (new_block != '1')	
		params->player.pos_x += side_vector[0] * MOVE_SPEED;
	new_block = params->map[(int)(params->player.pos_y
		+ side_vector[1] * MOVE_SPEED)][(int)params->player.pos_x];
	if (new_block != '1')	
		params->player.pos_y += side_vector[1] * MOVE_SPEED;
}

static void go_left(float *side_vector, t_params *params)
{
	char 	new_block;

	new_block = params->map[(int)params->player.pos_y]
		[(int)(params->player.pos_x - side_vector[0] * MOVE_SPEED)];
	if (new_block != '1')	
		params->player.pos_x -= side_vector[0] * MOVE_SPEED;
	new_block = params->map[(int)(params->player.pos_y
		- side_vector[1] * MOVE_SPEED)][(int)params->player.pos_x];
	if (new_block != '1')	
		params->player.pos_y -= side_vector[1] * MOVE_SPEED;
}

void	cub_move_player(int key, t_params *params)
{
	float	side_vector[2];

	if (key == FORWARD)
		go_forward(params);
	else if (key == BACKWARD)
		go_backward(params);
	else
	{
		side_vector[0] = -params->player.ori_y;
		side_vector[1] = params->player.ori_x;
		if (key == RIGHT)
			go_right(side_vector, params);
		else if (key == LEFT)
			go_left(side_vector, params);
	}
}