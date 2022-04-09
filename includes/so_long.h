#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libs/mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct s_gamedata
{
    char *game_name;
    int window_height;
    int window_width;

    void *mlx;
    void *mlx_window;

    char **map;

    void *wall;
    void *player;
    void *obstacle;
    void *collectable;
    void *background;
    void *exit;
    
    char *map_destination;

    int image_size;
    int has_error;

} t_gamedata;


#endif