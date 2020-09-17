#include "../includes/cub.h"

void	cub_free_params(t_params params)
{
	free(params.path_sprite);
	free(params.path_no);
	free(params.path_so);
	free(params.path_we);
	free(params.path_ea);
}

static bool check_extension(char *file, char *extension)
{
	int i;

	i = 0;
	while (file[i] != '.')
	{
		if (file[i] == '\0')
			return (false);
		i++;
	}
	if (ft_strncmp(file + ++i, extension, 4))
		return (false);
	return (true);	
}

static int	check_get_fd(char *file)
{
	int fd;

	if (!check_extension(file, "cub"))
	{
		dprintf(1, "Error\n%s\n", strerror(errno));
		return (-1);
	}
	if ((fd = open(file, O_RDONLY)) < 0)
	{
		dprintf(1, "Error\n%s\n", strerror(errno));
		return (-1);
	}
	return (fd);
}

static void	prep_tool_param(t_pars_tool *check, t_params *params)
{
	check->window = false;
	check->ceiling = false;
	check->floor = false;
	check->map = false;
	params->path_ea = NULL;
	params->path_no = NULL;
	params->path_we = NULL;
	params->path_so = NULL;
	params->path_sprite = NULL;
}

/*
** checks if we have all the params (except map)
*/

static bool	check_all_tools(t_pars_tool to_check, t_params params)
{
	if (!to_check.window || !to_check.ceiling || !to_check.floor
	|| !params.path_ea || !params.path_we || !params.path_no
	|| !params.path_sprite || !params.path_so)
		return (false);
	return (true);
}

/*
** word = ensemble de caractères séparés par des espaces
*/

static char	*get_next_word(char *str)
{
	int		i;
	char	*word;

	i = 0;
	while (str[i] && ft_isalnum(str[i]))
		i++;
	if (!(word = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	ft_strlcpy(word, str, i + 1);
	return (word);
}

static bool	cpy_path(char *old, char *new)
{
	if (old == NULL)
	{
		old = new;
		return (true);
	}
	free(new);
	return (false);
}

static int	store_wall_fd(char *word, char *line, t_params *params)
{
	char	*new_path;
	int		i;

	i = ft_strlen(word);
	while (line[i] && line[i] == ' ')
		i++;
	if (!(new_path = get_next_word(line + i)))
		return (-1);
	if (!ft_strncmp(word, "EA", 3))
		return (cpy_path(params->path_ea, new_path));
	else if (!ft_strncmp(word, "WE", 3))
		return (cpy_path(params->path_we, new_path));
	else if (!ft_strncmp(word, "NO", 3))
		return (cpy_path(params->path_no, new_path));
	else if (!ft_strncmp(word, "SO", 3))
		return (cpy_path(params->path_so, new_path));
	return (false);
}

static bool	store_window_r(char *line, t_params *params, t_pars_tool *tool)
{
	int i;

	if (tool->window == true)
		return (false);
	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	params->window_xy[0] = ft_atoi(line + i);
	i = i + ft_strlen(ft_itoa(params->window_xy[0]));
	params->window_xy[1] = ft_atoi(line + i);
	if (params->window_xy[0] < 0 || params->window_xy[1] < 0)
		return (false);
	return (true);
}

static bool conv_rgb_int(char **tab, int *final_rgb)
{
	int	i;
	int	j;
	int	k;
	int	number;

	i = 0;
	k = 23;
	while (tab[i])
	{
		number = ft_atoi(tab[i++]);
		if (number > 255 || k <= 0)
			return (false);
		j = 7;
		while (j >= 0)
		{
			*final_rgb += (number / (int)pow(2, j)) * pow(2, k--);
			number = number % (int)pow(2, j--);
		}
	}
	if (i != 3)
		return (false);
	return (true);
}

static int cpy_rgb(int *rgb, char *str)
{
	bool	ret;
	int		i;
	char  	**tab;

	tab = NULL;
	while (str[0] == ' ')
		str++;
	if (!(tab = ft_split(str, ',')))
		return (-1);
	ret = conv_rgb_int(tab, rgb);
	i = 0;
	while (tab[i])
		free(tab[i++]);
	return (ret);
}

static bool	store_rgb(char *word, char *line, t_params *params, t_pars_tool *tool)
{
	int	i;

	i = ft_strlen(word);
	if (!ft_strncmp(word, "F", 2))
	{
		if (tool->floor == true)
			return (false);
		tool->floor = true;
		return (cpy_rgb(&params->floor_rgb, line + i));
	}
	else if (!ft_strncmp(word, "C", 2))
	{
		if (tool->ceiling == true)
			return (false);
		tool->ceiling = true;
		return (cpy_rgb(&params->ceiling_rgb, line + i));
	}
	return (true);
}

static int process_line(char *line, t_params *params, t_pars_tool *tool)
{
	char	*word;
	int		ret;

	if (line[0] == 0)
		return (true);
	if (!(word = get_next_word(line)))
		return (-1);
	if (!ft_strncmp(word, "EA", 3) || !ft_strncmp(word, "NO", 3)
	|| !ft_strncmp(word, "SO", 3) || !ft_strncmp(word, "WE", 3))
		ret = store_wall_fd(word, line, params);
	else if (!ft_strncmp(word, "F", 2) || !ft_strncmp(word, "C", 2))
		ret = store_rgb(word, line, params, tool);
	else if (!ft_strncmp(word, "R", 2))
		ret = store_window_r(line + ft_strlen(word), params, tool);
	else
	{
		free(word);
		return (false);
	}
	free(word);
	return (ret);
}

static bool	check_pl_ret(int ret_pl, t_params params)
{
	if (ret_pl == -1)
	{
		dprintf(1, "Error\n%s\n", strerror(errno));
		cub_free_params(params);
		exit(EXIT_FAILURE);
	}
	else if (ret_pl == 0)
	{
		cub_free_params(params);
		return (false);
	}
	return (true);
}

static bool	pars_file(int fd, t_params *params)
{
	t_pars_tool tool;
	char		*line;
	int			ret_gnl;
	int			ret_pl;

	prep_tool_param(&tool, params);
	while ((ret_gnl = get_next_line(fd, &line)) > 0)
	{
		ret_pl = process_line(line, params, &tool);
		free(line);
		if (!check_pl_ret(ret_pl, *params))
			return (false);
	}
	if (ret_gnl == -1)
	{
		dprintf(1, "Error\n%s\n", strerror(errno));
		free(line);
		cub_free_params(*params);
		exit(EXIT_FAILURE);
	}
	ret_pl = process_line(line, params, &tool);
	free(line);
	if (!check_pl_ret(ret_pl, *params))
		return (false);
	return (true);
}

bool		cub_pars(char *file, t_params *params)
{
	int			fd;

	if ((fd = check_get_fd(file) < 0))
	{
		dprintf(1, "Error\n%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	if (!pars_file(fd, params))
	{
		dprintf(1, "Error\nMap error\n");
		exit(EXIT_FAILURE);
	}
	return (true);
}
