#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include "libft.h"
# include <stdbool.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>

typedef struct	s_params
{
	int		window_xy[2];
	int		fd_no;
	int		fd_so;
	int		fd_ea;
	int 	fd_we;
	int		fd_sprite;
	int		floor_rgb[3];
	int		ceiling_rgb[3];
}				t_params;

typedef struct	s_pars_tool
{
	bool	window;
	bool	floor;
	bool	ceiling;
	bool	sprite;
	bool	no;
	bool	so;
	bool	ea;
	bool	we;
	bool	map;
	bool	error;
}				t_pars_tool;

bool			cub_pars(char *map_file, t_params *params);

#endif