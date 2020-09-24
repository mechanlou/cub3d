#include "cub.h"

static void	check_args(int argc, char **argv)
{
	if (argc < 2)
	{
		dprintf(1, "Error\nNo argument.\n");
		exit(EXIT_FAILURE);
	}
	else if (argc > 3)
	{
		dprintf(1, "%s\n", strerror(E2BIG));
		exit(EXIT_FAILURE);
	}
	else if (argc == 3 && ft_strncmp(argv[2], "--save", 7))
	{
		dprintf(1, "Error\nChing Chong, second argument is wrong.\n");
		exit(EXIT_FAILURE);
	}
}

int			main (int argc, char **argv)
{
	t_params 	params;

	dprintf(1, "====================\nBienvenue dans Cub3D\n\n");
	check_args(argc, argv);
	cub_pars(argv[1], &params);
	dprintf(1, "map bien\n");
	if (argc == 3)
		dprintf(1, "mdr je sais pas faire les screenshots\n");
	cub_free_params(params);
	return (EXIT_SUCCESS);
}