#include "cub.h"

int		cub_free_tab(void **tab, int ret)
{
	int i;

	if (tab)
	{
		i = 0;
		while (tab[i])
			free(tab[i++]);
	}
	free(tab);
	return (ret);
}

int		cub_rgbtoi(int r, int g, int b)
{
	int j;
	int k;
	int final_rgb;

	k = 23;
	j = 7;
	final_rgb = 0;
	while (j >= 0)
	{
		final_rgb += (r / (int)pow(2, j)) * pow(2, k--);
		r = r % (int)pow(2, j--);
	}
	j = 7;
	while (j >= 0)
	{
		final_rgb += (g / (int)pow(2, j)) * pow(2, k--);
		g = g % (int)pow(2, j--);
	}
	j = 7;
	while (j >= 0)
	{
		final_rgb += (b / (int)pow(2, j)) * pow(2, k--);
		b = b % (int)pow(2, j--);
	}
	return (final_rgb);
}

int		**cub_get_texture_infos(t_params params, t_print_vars *vars)
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
	while (texture[0][vars->tex_size[1]] != -2147483648)
		vars->tex_size[1]++;
	return (texture);
}
