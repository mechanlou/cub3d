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

bool cub_pars(char *file)
{
	int fd;

	if ((fd = check_get_fd(file) < 0))
		return (false);
	
	return (true);
}