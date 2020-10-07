#include "cub.h"

static void	close_image(void *mlx_ptr, void *img)
{
	mlx_destroy_image(mlx_ptr, img);
}

static int	**free_tab(int **tab)
{
	int i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (NULL);
}

static int	**cpy_img_tab(char *data, int *tab)
{
	int	**picture;
	int x;
	int y;
	int i;

	if (!(picture = malloc(sizeof(int *) * (tab[0] + 1))))
		return (NULL);
	x = 0;
	while (x < tab[0])
	{
		if (!(picture[x] = malloc(sizeof(int) * (tab[1] + 1))))
			return (free_tab(picture));
		y = 0;
		while (y < tab[1])
		{
			i = x * (tab[2] / 8) + y * tab[3];
			picture[x][y++] = (tab[4] == 1)
				? cub_rgbtoi(data[i + 1], data[i + 2], data[i + 3])
				: cub_rgbtoi(data[i + 2], data[i + 1], data[i + 0]);
		}
		picture[x][y] = -1;
		x++;
	}
	picture[x] = NULL;
	return (picture);
}

/*
** tab[0] = width
** tab[1] = height
** tab[2] = bits per pixel
** tab[3] = line size
** tab[4] = endian (0 = little / 1 = big)
*/

static int	**file_to_tab(void *mlx_ptr, char *file)
{
	void	*img;
	char	*data;
	int		**stuff;
	int		tab[5];

	if (!(img = mlx_xpm_file_to_image(mlx_ptr, file, &tab[0], &tab[1])))
		return (NULL);
	if (!(data = mlx_get_data_addr(img, &tab[2], &tab[3], &tab[4])))
	{
		close_image(mlx_ptr, img);
		return (NULL);
	}
	stuff = cpy_img_tab(data, tab);
	mlx_destroy_image(mlx_ptr, img);
	return (stuff);
}

bool		cub_init_textures(t_params *params)
{
	params->textures.north = file_to_tab(params->mlx_ptr, params->path_no);
	params->textures.south = file_to_tab(params->mlx_ptr, params->path_so);
	params->textures.east = file_to_tab(params->mlx_ptr, params->path_ea);
	params->textures.west = file_to_tab(params->mlx_ptr, params->path_we);
	params->textures.sprite = file_to_tab(params->mlx_ptr,
		params->path_sprite);
	if (!params->textures.north || !params->textures.south
		|| !params->textures.east || !params->textures.west
		|| !params->textures.sprite)
		return (false);
	return (true);
}