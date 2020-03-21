#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include "libft.h"
# include <stdbool.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

bool	cub_pars(char *map_file);

typedef struct	s_params
{
	int		r_xy[2];
	char	*path_no;
	char	*path_so;
	char	*path_ea;
	char 	*path_we;
	char	*path_s;
	int		f_rgb[3];
	int		c_rgb[3];
}				t_params;

#endif