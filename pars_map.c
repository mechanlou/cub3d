#include "cub.h"

static bool is_map_line(char *line)
{
	int		i;
	bool	is_1;

	i = 0;
	is_1 = false;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'N'
		&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W'
		&& line[i] != '2' & line[i] != ' ')
			return (false);
		if (line[i] == '1')
			is_1 = true;
		i++;
	}
	return (is_1);
}

int		cub_store_line(char *line, char ***map)
{
	int		i;
	char	**new_map;

	i = 0;
	while (*map[i])
		i++;
	new_map = *map;
	if (!(*map = (char **)malloc(sizeof(char *) * (i + 2))))
		return (-1);
	i = 0;
	while (new_map[i])
	{
		*map[i] = new_map[i];
		i++;
	}
	if (!(*map[i++] = ft_strdup(line)))
		return (cub_free_all(1, *map));
	*map[i] = NULL;
	free(new_map);
	dprintf(1, "%d|%s\n", i, *map[i]);
	dprintf(1, "%d|%s\n", i, new_map[i]);
	return (true);
}

static bool	check_char_surround(char **map, int x, int y)
{
	if (y == 0 || x == 0 || !map[y + 1] || !map[y][x + 1])
		return (false);
	if ((int)ft_strlen(map[y - 1]) < x || (int)ft_strlen(map[y + 1]) < x)
		return (false);
	if (map[y][x + 1] == ' ' || map[y][x - 1] == ' '
	|| map[y + 1][x] == ' ' || map[y - 1][x] == ' ')
		return (false);
	return (true);
}

static bool	pars_map(char **map)
{
	int	x;
	int	y;
	int nb_nsew;

	nb_nsew = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0' || map[y][x] == '2'
			|| map[y][x] == 'N' || map[y][x] == 'S'
			|| map[y][x] == 'E' || map[y][x] == 'W')
			{
				if (!check_char_surround(map, x, y))
					return (false);
			}
			if (map[y][x] == 'N' || map[y][x] == 'S'
			|| map[y][x] == 'E' || map[y][x] == 'W')
				nb_nsew++;
			x++;
		}
		y++;
	}
	return (nb_nsew == 1);
}

int		cub_store_map(char *line, t_params *params, t_pars_tool *tool)
{
	if (!*line)
	{
		if (tool->map_start)
		{
			tool->map_end = true;
			return (pars_map(params->map));
		}
		else
			return (true);
	}
	else if (tool->map_end)
		return (false);
	tool->map_start = true;
	if (!is_map_line(line))
		return (false);
	return (cub_store_line(line, &params->map));
}