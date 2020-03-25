#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include "libft.h"
# include <stdbool.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

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
	bool	error;
}				t_params;

typedef struct	s_pars_tool
{
	bool	r;
	bool	f;
	bool	c;
	bool	s;
	bool	no;
	bool	so;
	bool	ea;
	bool	we;
	bool	map;
}				t_pars_tool;

t_params		cub_pars(char *map_file);

#endif