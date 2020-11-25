#include "cub.h"

/*
** word = ensemble de caractères séparés par des espaces
*/

static bool	free_page(char **str)
{
	int i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	return (false);
}

char		*cub_get_next_word(char *str)
{
	int		i;
	char	*word;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	if (!(word = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	ft_strlcpy(word, str, i + 1);
	return (word);
}

static int	process_line(char *line, t_params *params, t_pars_tool *tool)
{
	char	*word;
	int		ret;

	if (cub_check_all_tools(*tool, *params))
		return (cub_store_map(line, params, tool));
	if (line[0] == 0)
		return (true);
	if (!(word = cub_get_next_word(line)))
		return (-1);
	if (!ft_strncmp(word, "EA", 3) || !ft_strncmp(word, "NO", 3)
	|| !ft_strncmp(word, "SO", 3) || !ft_strncmp(word, "WE", 3)
	|| !ft_strncmp(word, "S", 2))
		ret = cub_store_wall_path(word, line, params);
	else if (!ft_strncmp(word, "F", 2) || !ft_strncmp(word, "C", 2))
		ret = cub_store_rgb(word, line, params, tool);
	else if (!ft_strncmp(word, "R", 2))
		ret = cub_store_window_r(line + ft_strlen(word), params, tool);
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
		ft_printf("Error\n%s\n", strerror(errno));
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

bool		cub_pars_file(int fd, t_params *params)
{
	t_pars_tool tool;
	char		**page;
	int			ret_pl;
	int			i;

	if (cub_prep_tool_param(&tool, params) == -1)
		return (false);
	if (!(page = cub_store_page(fd)))
	{
		ft_printf("Error\n%s\n", strerror(errno));
		cub_free_params(*params);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (page[i])
	{
		ret_pl = process_line(page[i++], params, &tool);
		if (!check_pl_ret(ret_pl, *params))
			return (free_page(page));
	}
	free_page(page);
	if (!cub_check_all_tools(tool, *params))
		return (false);
	return (true);
}
