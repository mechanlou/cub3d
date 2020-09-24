#include "cub.h"

static bool	check_r_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (!str[i])
		return (false);
	while (ft_isdigit(str[i]))
		i++;
	if (!str[i])
		return (false);
	while (str[i] == ' ')
		i++;
	if (!str[i])
		return (false);
	while (ft_isdigit(str[i]))
		i++;
	while (str[i] == ' ')
		i++;
	if (!str[i])
		return (true);
	return (false);
}

static bool	cpy_path(char **old, char *new)
{
	if (*old == NULL)
	{
		*old = new;
		return (true);
	}
	free(new);	
	return (false);
}

int	cub_store_wall_path(char *word, char *line, t_params *params)
{
	char	*new_path;
	int		i;
	int		ret;

	ret = false;
	i = ft_strlen(word);
	while (line[i] && line[i] == ' ')
		i++;
	if (!(new_path = ft_strdup(line + i)))
		return (-1);
	if (!ft_strncmp(word, "EA", 3))
		ret = cpy_path(&params->path_ea, new_path);
	else if (!ft_strncmp(word, "WE", 3))
		ret = cpy_path(&params->path_we, new_path);
	else if (!ft_strncmp(word, "NO", 3))
		ret = cpy_path(&params->path_no, new_path);
	else if (!ft_strncmp(word, "SO", 3))
		ret = cpy_path(&params->path_so, new_path);
	else if (!ft_strncmp(word, "S", 2))
		ret = cpy_path(&params->path_sprite, new_path);
	else
		free(new_path);
	return (ret);
}

int	cub_store_window_r(char *line, t_params *params, t_pars_tool *tool)
{
	int		i;
	char	*num;

	if (tool->window == true || !check_r_line(line))
		return (false);
	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	params->window_xy[0] = ft_atoi(line + i);
	if (!(num = ft_itoa(params->window_xy[0])))
		return (-1);
	i = i + ft_strlen(num);
	free(num);
	params->window_xy[1] = ft_atoi(line + i);
	if (params->window_xy[0] < 0 || params->window_xy[1] < 0)
		return (false);
	tool->window = true;
	return (true);
}