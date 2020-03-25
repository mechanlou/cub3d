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
		dprintf(1, "Error\nBroken file or doesn't exist i don't know\n");
		return (-1);
	}
	return (fd);
}

static void	prep_tool(t_pars_tool check)
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
}	

bool		pars_file(int fd, t_params params)
{
	t_pars_tool tool;

	prep_tool(tool);
	(void)fd;
	(void)params;
	return (true);
}

t_params	cub_pars(char *file)
{
	int			fd;
	t_params 	params;

	if ((fd = check_get_fd(file) < 0))
		return (false);
	return (pars_file(fd, params));
}