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

    char *wall_path;
    char *player_path;
    char *obstacle_path;
    char *collectible_path;
    char *background_path;
    char *exit_path;
    
    char *map_destination;

    int x;
    int y;

    int current_x;
    int current_y;

    int line_count;
    int line_size;

    int image_size;
    int has_error;

} t_gamedata;


#endif