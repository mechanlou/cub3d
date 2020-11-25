#include "cub.h"

float	**free_tab(float **tab)
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

float	**cub_core_function(bool already, t_print_vars vars, int s, float *new)
{
	float	**new_dists;
	int		i;

	if (already)
		return (vars.rel_sprites_pos);
	if (!(new_dists = malloc(sizeof(float *) * (s + 2))))
		return (NULL);
	i = -1;
	while (++i < s)
		new_dists[i] = vars.rel_sprites_pos[i];
	if (!(new_dists[i] = malloc(sizeof(float) * 2)))
		return (free_tab(new_dists));
	new_dists[i][0] = new[0];
	new_dists[i][1] = new[1];
	new_dists[i + 1] = NULL;
	free(vars.rel_sprites_pos);
	return (new_dists);
}

float	**cub_add_sprite_d(t_dda_vars dda, t_params p, t_print_vars vars)
{
	bool	already;
	int		size;
	float	new_xy[2];

	size = 0;
	new_xy[0] = dda.curr_square[0] - p.player.pos_x;
	new_xy[1] = dda.curr_square[1] - p.player.pos_y;
	already = false;
	while (vars.rel_sprites_pos && vars.rel_sprites_pos[size])
	{
		if (vars.rel_sprites_pos[size][0] == new_xy[0]
			&& vars.rel_sprites_pos[size][1] == new_xy[1])
			already = true;
		size++;
	}
	return (cub_core_function(already, vars, size, new_xy));
}
