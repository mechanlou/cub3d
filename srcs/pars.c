#include "cub.h"

static bool	check_extension(char *file, char *extension)
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

bool		cub_pars(char *file, t_params *params)
{
	int			fd;

	if ((fd = check_get_fd(file)) <= 0)
	{
		dprintf(1, "Error\n%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	if (!cub_pars_file(fd, params))
	{
		dprintf(1, "Error\nMap error\n");
		exit(EXIT_FAILURE);
	}
	return (true);
}
