#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libs/mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

enum keys
{
    W = 13,
	A = 0,
	S = 1,
	D = 2,
	ESC = 53
};

typedef struct s_gamedata
{
    char *game_name;
    int window_height;
    int window_width;

    void *mlx;
    void *mlx_window;

    char **map;

    void *wall_object;
    void *collectible_object;
    void *exit_object;
    void *player_up_object;
    void *player_left_object;
    void *player_down_object;
    void *player_right_object;
    
    char *map_destination;

    int x;
    int y;

    int current_x;
    int current_y;

    int map_coordinates_i;
    int map_coordinates_j;

    int line_count;
    int line_size;

    int image_size;
    int has_error;

    char current_direction;
    char *direction_path;

} t_gamedata;


#endif