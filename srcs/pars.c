#include "../includes/cub.h"

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
		dprintf(1, "Error\nThe file's extension is wrong\n");
		return (-1);
	}
	if ((fd = open(file, O_RDONLY)) < 0)
	{
		dprintf(1, "Error\nBroken file or doesn't exist i don't know fuck this\n");
		return (-1);
	}
	return (fd);
}

static void	prep_tool(t_pars_tool *check)
{
	check->r = false;
	check->s = false;
	check->c = false;
	check->f = false;
	check->no = false;
	check->so = false;
	check->ea = false;
	check->we = false;
	check->map = false;
	check->error = false;
}	

static bool	check_all_tools(t_pars_tool to_check)
{
	if (!to_check.r || !to_check.s || !to_check.c || !to_check.f
	|| !to_check.no || !to_check.so || !to_check.ea || !to_check.we
	|| !to_check.map)
		return (false);
	return (true);
}

static char	*get_next_element(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i])
		return (ft_strdup(line[i]));
	return (NULL);
}

static bool	pars_file(int fd, t_params *params)
{
	t_pars_tool tool;
	char		*line;
	int			ret;

	prep_tool(&tool);
	while (!check_all_tools(tool) && !tool.error)
	{
		while ((ret = get_next_line(fd, &line)) > 0 && line[0] != '\n')
		{
			
		}
	}
	(void)params;
	return (params);
}

bool		cub_pars(char *file, t_params *params)
{
	int			fd;

	if ((fd = check_get_fd(file) < 0))
		return (false);
	return (pars_file(fd, params));
}