#include "../includes/so_long.h"

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
	gamedata->current_direction = 'S';
	gamedata->map_destination = argv[1];
	if (argc == 0)
		exit_game(gamedata, NULL, 0);
	game_init(gamedata);
	read_map(gamedata);
	render_map(gamedata);
	mlx_hook(gamedata->mlx_window, 2, 1L << 0, key_event, gamedata);
	mlx_hook(gamedata->mlx_window, 17, 1L << 17, exit_game, gamedata);
	mlx_loop(gamedata->mlx);
	return (0);
}
