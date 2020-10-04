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
# include <mlx.h>
# include "key.h" 
# include <math.h>

# define FORWARD	K_W
# define LEFT		K_A
# define BACKWARD	K_S
# define RIGHT		K_D

# define FOV_SIZE		0.66
# define ROTATE_SPEED	0.22
# define MOVE_SPEED		0.2

typedef struct s_dda_vars
{
	float 	ray_dir[2];
	int 	curr_square[2];
	float	side_dist[2];
	float	delta_dist[2];
	int		step[2];
	int		side;
}				t_dda_vars;


typedef struct	s_player
{
	float		pos_x;
	float		pos_y;
	float		ori_x;
	float		ori_y;
	float		cam_x;
	float		cam_y;
}				t_player;

typedef struct	s_textures
{
	char		**north;
	char		**south;
	char		**east;
	char		**west;
	char		**sprite;
}				t_textures;


typedef struct	s_params
{
	void		*mlx_ptr;
    void		*win_ptr;
	int			window_xy[2];
	char	 	*path_no;
	char	 	*path_so;
	char	 	*path_ea;
	char	 	*path_we;
	char	 	*path_sprite;
	int			floor_rgb;
	int			ceiling_rgb;
	char		**map;
	t_textures	textures;
	t_player	player;
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
int				cub_key_release_hook(int key, t_params *params);
int				cub_key_press_hook(int key, t_params *params);
void			cub_the_game(t_params params, int argc);
int				cub_put_map(t_params params);
void			cub_move_player(int key, t_params *params);

#endif
