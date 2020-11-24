#include "cub.h"

/*
**	wall_spot[0] = which face (in char)
**	wall_spot[1] = x position of the ray on this wall
*/

static void ceiling_to_image(int x, t_params params, int start, t_image *image)
{
	int		i;
	char	ceiling_color[4];

	if (image->endian == 1)
	{
		ceiling_color[0] = 0;
		ceiling_color[1] = (params.ceiling_rgb >> (2 * 8) & 255);
		ceiling_color[2] = (params.ceiling_rgb >> (1 * 8) & 255);
		ceiling_color[3] = (params.ceiling_rgb & 255);
	}
	else
	{
		ceiling_color[0] = (params.ceiling_rgb & 255);
		ceiling_color[1] = (params.ceiling_rgb >> (1 * 8) & 255);
		ceiling_color[2] = (params.ceiling_rgb >> (2 * 8) & 255);
		ceiling_color[3] = 0;
	}
	i = 0;
	while (i < start)
	{
		image->data[x * 4 + image->line_size * i + 0] = ceiling_color[0];
		image->data[x * 4 + image->line_size * i + 1] = ceiling_color[1];
		image->data[x * 4 + image->line_size * i + 2] = ceiling_color[2];
		image->data[x * 4 + image->line_size * i++ + 3] = ceiling_color[3];
	}
}

void		cub_pixel_to_image(t_image *image, int x, int y, int rgb)
{
	if (image->endian == 1)
	{
		image->data[x * 4 + image->line_size * y + 3] = (rgb & 255);
		image->data[x * 4 + image->line_size * y + 2] = (rgb >> (1 * 8) & 255);
		image->data[x * 4 + image->line_size * y + 1] = (rgb >> (2 * 8) & 255);
		image->data[x * 4 + image->line_size * y + 0] = 0;
	}
	else
	{
		image->data[x * 4 + image->line_size * y + 0] = (rgb & 255);
		image->data[x * 4 + image->line_size * y + 1] = (rgb >> (1 * 8) & 255);
		image->data[x * 4 + image->line_size * y + 2] = (rgb >> (2 * 8) & 255);
		image->data[x * 4 + image->line_size * y + 3] = 0;
	}	
}

static void	walls_to_image(int x, t_params p, t_print_vars v, t_image *image)
{
	int		i;
	int		**texture;
	float	tex_spot;

	texture = cub_get_texture_infos(p, &v);
	v.tex_pos[0] = (int)(v.wall_x * (float)v.tex_size[0]);
	v.step = (float)v.tex_size[1] / (float)v.line_height;
	tex_spot = (v.start - p.window_xy[1] / 2 + v.line_height / 2) * v.step;
	i = v.start;
	while (i < v.end)
	{
		v.tex_pos[1] = (int)tex_spot;
		tex_spot += v.step;
		cub_pixel_to_image(image, x, i++, texture[v.tex_pos[0]][v.tex_pos[1]]);
	}
}

static void floor_to_image(int x, t_params p, t_print_vars v, t_image *image)
{
	int		i;
	char	floor_color[4];

	if (image->endian == 1)
	{
		floor_color[0] = 0;
		floor_color[1] = (p.floor_rgb >> (2 * 8) & 255);
		floor_color[2] = (p.floor_rgb >> (1 * 8) & 255);
		floor_color[3] = (p.floor_rgb >> (0 * 8) & 255);
	}
	else
	{
		floor_color[0] = (p.floor_rgb >> (0 * 8) & 255);
		floor_color[1] = (p.floor_rgb >> (1 * 8) & 255);
		floor_color[2] = (p.floor_rgb >> (2 * 8) & 255);
		floor_color[3] = 0;
	}
	i = v.end;
	while (i < p.window_xy[1])
	{
		image->data[x * 4 + image->line_size * i + 0] = floor_color[0];
		image->data[x * 4 + image->line_size * i + 1] = floor_color[1];
		image->data[x * 4 + image->line_size * i + 2] = floor_color[2];
		image->data[x * 4 + image->line_size * i++ + 3] = floor_color[3];
	}
}

bool		cub_sc_l(t_params p, float **b, t_print_vars *v, t_image *i)
{
	float			wall_dist;

	wall_dist = cub_cast_ray(
		2 * (float)v->sprite_size / p.window_xy[0] - 1, p, v);
	if (wall_dist == -1)
		return (false);
	v->line_height = (int)(p.window_xy[1] / wall_dist);
	v->start = -v->line_height / 2 + p.window_xy[1] / 2;
	if (v->start < 0)
		v->start = 0;
	v->end = v->line_height / 2 + p.window_xy[1] / 2;
	if (v->end > p.window_xy[1] || v->end < 0)
		v->end = p.window_xy[1];
	ceiling_to_image(v->sprite_size, p, v->start, i);
	walls_to_image(v->sprite_size, p, *v, i);
	floor_to_image(v->sprite_size, p, *v, i);
	b[0][v->sprite_size] = wall_dist;
	return (true);
}