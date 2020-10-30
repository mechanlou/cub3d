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
		dprintf(1, "Error\n%s\n", strerror(E2BIG));
		exit(EXIT_FAILURE);
	}
	else if (argc == 3 && ft_strncmp(argv[2], "--save", 7))
	{
		dprintf(1, "Error\nChing Chong, second argument is wrong.\n");
		exit(EXIT_FAILURE);
	}
}

int			main(int argc, char **argv)
{
	t_params	params;

	check_args(argc, argv);
	cub_pars(argv[1], &params);
	cub_the_game(params, argc);
	cub_free_params(params);
	return (EXIT_SUCCESS);
}
