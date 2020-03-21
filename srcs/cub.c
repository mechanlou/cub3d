#include "../includes/cub.h"

static bool	check_args(int argc, char **argv)
{
	if (argc < 2)
	{
		dprintf(1, "Error\nNo argument\n");
		return (false);
	}
	else if (argc > 3)
	{
		dprintf(1, "Error\nToo many arguments\nbitch\n");
		return (false);
	}
	else if (argc == 3 && ft_strncmp(argv[2], "--save", 7))
	{
		dprintf(1, "Error\nSecond argument is wrong\n");
		return (false);
	}
	return (true);
}

int			main (int argc, char **argv)
{
	dprintf(1, "Bienvunue dans Cub3D\n\n");
	if (!check_args(argc, argv))
		return (0);
	if (cub_pars(argv[1]))
	{
		dprintf(1, "map bien\n");
		if (argc == 3)
			dprintf(1, "mdr je sais pas faire les screenshots\n");
	}
	return (0);
}