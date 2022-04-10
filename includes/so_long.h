#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libs/mlx/mlx.h"
# include "../libs/ft_printf/ft_printf.h"
# include "../libs/Libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

enum	e_keys
{
	W = 13,
	A = 0,
	S = 1,
	D = 2,
	ESC = 53
};

typedef struct s_gamedata
{
	int		window_height;
	int		window_width;

	void	*mlx;
	void	*mlx_window;

	char	**map;

	void	*wall_object;
	void	*collectible_object;
	void	*exit_object;
	void	*player_up_object;
	void	*player_left_object;
	void	*player_down_object;
	void	*player_right_object;

	char	*map_destination;

	int		x;
	int		y;

	int		current_x;
	int		current_y;

	int		map_coordinates_i;
	int		map_coordinates_j;

	int		line_count;
	int		line_size;

	int		image_size;

	int		collectible_count;
	int		player_spawn_point_count;
	int		exit_count;
	int		collectible_size;

	int		player_move_count;

	char	current_direction;
	char	*direction_path;

}	t_gamedata;

int		exit_game(t_gamedata *gamedata, char *str, int exit_mode);
int		key_event(int key, t_gamedata *gamedata);

void	instantiate_wall(t_gamedata *gamedata, int x, int y);
void	instantiate_collectible(t_gamedata *gamedata, int x, int y);
void	instantiate_exit(t_gamedata *gamedata, int x, int y);
void	instantiate_player(t_gamedata *gamedata, int x, int y);
void	instantiate_player_direction(t_gamedata *gamedata, void *img);

void	move_character_up(t_gamedata *gamedata);
void	move_character_left(t_gamedata *gamedata);
void	move_character_down(t_gamedata *gamedata);
void	move_character_right(t_gamedata *gamedata);
void	player_movement(t_gamedata *gamedata, int current_x, int current_y);

int		get_line_count(t_gamedata *gamedata);
int		get_line_size(t_gamedata *gamedata);
int		get_file_length(t_gamedata *gamedata);
void	get_initial_informations(t_gamedata *gamedata);
void	read_map(t_gamedata *gamedata);

void	get_object_path(t_gamedata *gamedata);
void	instantiate_world(t_gamedata *gamedata, int x, int y, char object);
void	render_map(t_gamedata *gamedata);
void	free_map(char **map);

#endif