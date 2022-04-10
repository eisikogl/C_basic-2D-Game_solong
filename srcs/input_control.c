#include "../includes/so_long.h"

int	exit_game(t_gamedata *gamedata, char *str, int exit_mode)
{
	if (str)
		ft_printf("ERROR\n%s You left dude come back... ", str);
	if (exit_mode == 2)
		ft_printf("Congrats! You`ve succesfully trapped the Kittens in the Tree");
	if (gamedata->wall_object)
		mlx_destroy_image(gamedata->mlx, gamedata->wall_object);
	if (gamedata->collectible_object)
		mlx_destroy_image(gamedata->mlx, gamedata->collectible_object);
	if (gamedata->exit_object)
		mlx_destroy_image(gamedata->mlx, gamedata->exit_object);
	if (gamedata->player_up_object)
		mlx_destroy_image(gamedata->mlx, gamedata->player_up_object);
	if (gamedata->player_left_object)
		mlx_destroy_image(gamedata->mlx, gamedata->player_left_object);
	if (gamedata->player_down_object)
		mlx_destroy_image(gamedata->mlx, gamedata->player_down_object);
	if (gamedata->player_right_object)
		mlx_destroy_image(gamedata->mlx, gamedata->player_right_object);
	if (gamedata->map)
		free_map(gamedata->map);
	if (gamedata)
		free(gamedata);
	exit(exit_mode);
}

int	key_event(int key, t_gamedata *gamedata)
{
	if (key == W)
		move_character_up(gamedata);
	if (key == A)
		move_character_left(gamedata);
	if (key == S)
		move_character_down(gamedata);
	if (key == D)
		move_character_right(gamedata);
	if (key == ESC)
	{
		ft_printf("You left dude come back...");
		exit_game(gamedata, NULL, 0);
	}
	return (0);
}
