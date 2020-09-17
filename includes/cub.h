#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include "libft.h"
# include <stdbool.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <math.h>


typedef struct	s_params
{
	int		window_xy[2];
	char 	*path_no;
	char 	*path_so;
	char 	*path_ea;
	char 	*path_we;
	char 	*path_sprite;
	int		floor_rgb;
	int		ceiling_rgb;
}				t_params;

typedef struct	s_pars_tool
{
	bool	window;
	bool	floor;
	bool	ceiling;
	bool	map;
}				t_pars_tool;

bool			cub_pars(char *map_file, t_params *params);
void			cub_free_params(t_params params);

#endif
