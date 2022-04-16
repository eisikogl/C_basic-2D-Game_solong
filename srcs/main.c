#include "../includes/so_long.h"

void	start_init(t_gamedata *gamedata)
{
	gamedata->player_up_object = NULL;
	gamedata->player_left_object = NULL;
	gamedata->player_down_object = NULL;
	gamedata->player_right_object = NULL;
	gamedata->wall_object = NULL;
	gamedata->collectible_object = NULL;
	gamedata->exit_object = NULL;
	gamedata->direction_path = NULL;
	gamedata->mlx = NULL;
	gamedata->map = NULL;
	gamedata->mlx_window = NULL;
	gamedata->current_direction = 'S';
	gamedata->current_x = 0;
	gamedata->current_y = 0;
	gamedata->image_size = 0;
	gamedata->collectible_count = 0;
	gamedata->player_move_count = 0;
	gamedata->window_height = 0;
	gamedata->window_width = 0;
	gamedata->player_spawn_point_count = 0;
	gamedata->exit_count = 0;
}

void	game_init(t_gamedata *gamedata)
{
	void	*mlx_window;
	void	*mlx;

	mlx = mlx_init();
	gamedata->mlx = mlx;
	gamedata->window_width = 64 * get_line_size(gamedata);
	gamedata->window_height = 64 * get_line_count(gamedata);
	mlx_window = mlx_new_window(gamedata->mlx, gamedata->window_width, \
		gamedata->window_height, "Kitten grab`n trapp ");
	gamedata->mlx_window = mlx_window;
}

int	main(int argc, char **argv)
{
	t_gamedata	*gamedata;

	gamedata = malloc(sizeof(t_gamedata));
	if (!gamedata)
		perror("Error\n");
	start_init(gamedata);
	if (argc != 2)
		exit_game(gamedata, 0);
	gamedata->map_destination = argv[1];
	read_map(gamedata);
	map_validate(gamedata);
	validate(gamedata);
	game_init(gamedata);
	render_map(gamedata);
	mlx_hook(gamedata->mlx_window, 2, 1L << 0, key_event, gamedata);
	mlx_hook(gamedata->mlx_window, 17, 1L << 17, exit_game, gamedata);
	mlx_loop(gamedata->mlx);
	return (0);
}
