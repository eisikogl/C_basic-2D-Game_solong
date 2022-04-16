#include "../includes/so_long.h"

int	get_line_count(t_gamedata *gamedata)
{
	char	c;
	int		line_count;
	int		fd;

	fd = open(gamedata->map_destination, O_RDONLY);
	if (fd < 0)
		exit_game(gamedata,0);
	line_count = 0;
	while (read(fd, &c, 1))
	{
		if (c == '\n')
			line_count++;
	}
	close(fd);
	return (line_count + 1);
}

int	get_line_size(t_gamedata *gamedata)
{
	char	c;
	int		line_size;
	int		fd;

	fd = open(gamedata->map_destination, O_RDONLY);
	if (fd < 0)
		exit_game(gamedata,0);
	line_size = 0;
	while (read(fd, &c, 1))
	{
		if (c == '\n')
			break ;
		line_size++;
	}
	close(fd);
	return (line_size);
}

int	get_file_length(t_gamedata *gamedata)
{
	char	c;
	int		i;
	int		fd;

	i = 0;
	fd = open(gamedata->map_destination, O_RDONLY);
	if (fd < 0)
		exit_game(gamedata,0);
	while (read(fd, &c, 1))
	{
		i++;
	}
	close(fd);
	return (i);
}

void	get_initial_informations(t_gamedata *gamedata)
{
	int	i;
	int	j;

	i = 0;
	while (gamedata->map[i])
	{
		j = 0;
		while (gamedata->map[i][j])
		{
			if (gamedata->map[i][j] == 'P')
			{
				gamedata->player_spawn_point_count += 1;
				gamedata->current_x = i;
				gamedata->current_y = j;
			}
			if (gamedata->map[i][j] == 'C')
				gamedata->collectible_size += 1;
			if (gamedata->map[i][j] == 'E')
				gamedata->exit_count += 1;
			// if (gamedata->map[i][j] != '0' 'E' 'P' 'C')
			// 	exit_game(gamedata, 0);
			j++;
		}
		i++;
	}
	ft_printf("Moves: %d \n", gamedata->player_move_count);
}

void	read_map(t_gamedata *gamedata)
{
	int		fd;
	int		file_length;
	char	*map;

	file_length = get_file_length(gamedata);
	map = (char *)malloc(file_length + 1);
	if (!map)
		exit_game(gamedata,0);
	fd = open(gamedata->map_destination, O_RDONLY);
	if (fd < 0)
		exit_game(gamedata,0);
	read(fd, map, file_length);
	gamedata->map = ft_split(map, '\n');
	get_initial_informations(gamedata);
	close(fd);
	free(map);
}
