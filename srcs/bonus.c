#include "../includes/so_long.h"

void	instantiate_enemy(t_gamedata *gamedata, int x, int y)
{
	void	*img;
	char	*path;

	path = "./assets/enemy/dog.xpm";
	img = mlx_xpm_file_to_image(gamedata->mlx, path, \
		&gamedata->image_size, &gamedata->image_size);
	gamedata->exit_object = img;
	mlx_put_image_to_window(gamedata->mlx, gamedata->mlx_window, img, x, y);
}

void	instantiate_world_bonus(t_gamedata *gamedata, int x, int y, char object)
{
	if (object == 'e')
		instantiate_enemy(gamedata, x, y);
}