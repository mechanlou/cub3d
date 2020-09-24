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
	char	**map;
}				t_params;

typedef struct	s_pars_tool
{
	bool	window;
	bool	floor;
	bool	ceiling;
	bool	map_start;
	bool	map_end;
}				t_pars_tool;

bool			cub_pars(char *map_file, t_params *params);
int				cub_prep_tool_param(t_pars_tool *check, t_params *params);
bool			cub_check_all_tools(t_pars_tool to_check, t_params params);
void			cub_free_params(t_params params);
char			*cub_get_next_word(char *str);
bool			cub_pars_file(int fd, t_params *params);
bool			cub_store_rgb(char *word, char *line, t_params *params, t_pars_tool *tool);
int				cub_store_wall_path(char *word, char *line, t_params *params);
int				cub_store_window_r(char *line, t_params *params, t_pars_tool *tool);
int				cub_store_map(char *line, t_params *params, t_pars_tool *tool);
bool			cub_check_all_tools(t_pars_tool to_check, t_params params);
int				cub_free_all(const int number, ...);
char			**cub_store_page(int fd);
char			**cub_store_line(char *line, char **map);

#endif
