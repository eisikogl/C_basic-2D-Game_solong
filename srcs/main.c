#include "../includes/so_long.h"

#pragma region utils
//UTILS
size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}
void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (str);
}
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (ptr);
	ft_bzero(ptr, count * size);
	return (ptr);
}
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	char	*p;
	size_t	size;

	if (s == NULL)
		return (NULL);
	size = ft_strlen(s);
	if (start > size)
		return ((char *)ft_calloc(1, 1));
	if (start + len > size)
		len = size - start;
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	p = dest;
	while (len--)
		*dest++ = *(s + start++);
	*dest = '\0';
	return (p);
}

static size_t	ft_next_charset(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static size_t	ft_count_words(const char *s, char c)
{
	char	pre_c;
	size_t	i;

	i = 0;
	pre_c = c;
	while (*s)
	{
		if (pre_c == c && *s != c)
			i++;
		pre_c = *s;
		s++;
	}
	return (i);
}

char	**ft_split(const char *s, char c)
{
	char	**tab;
	size_t	next_charset;
	size_t	i;

	if (s == NULL)
		return (NULL);
	tab = malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (*s)
	{
		next_charset = ft_next_charset(s, c);
		if (next_charset)
		{
			tab[i] = ft_substr(s, 0, next_charset);
			s += next_charset;
			i++;
		}
		else
			s++;
	}
	tab[i] = NULL;
	return (tab);
}
#pragma endregion

int get_line_count(t_gamedata *gamedata)
{
	char c;
	int line_count;
    int fd;

    fd = open(gamedata->map_destination, O_RDONLY);
	line_count = 0;
	while(read(fd, &c, 1))
	{
		if (c == '\n')
			line_count++;
	}
    close(fd);
	return line_count + 1;
}

int get_line_size(t_gamedata *gamedata)
{
	char c;
	int line_size;
    int fd;

    fd = open(gamedata->map_destination, O_RDONLY);
	line_size = 0;
	while(read(fd, &c, 1))
	{
		if (c == '\n')
			break ;
		line_size++;
	}
    close(fd);
	return line_size;
}

int get_file_length(t_gamedata *gamedata)
{
	char c;
	int i = 0;
    int fd;

    fd = open(gamedata->map_destination, O_RDONLY);
	while(read(fd, &c, 1))
	{
		i++;
	}
    close(fd);
	return i;
}

void instantiate_wall(t_gamedata *gamedata, int x, int y)
{
	void	*img;
	char *path;

	path = "./assets/walls/wall2.xpm";
	img = mlx_xpm_file_to_image(gamedata->mlx, path, &gamedata->image_size, &gamedata->image_size);
	gamedata->wall_object = img;
    mlx_put_image_to_window(gamedata->mlx, gamedata->mlx_window, img, x, y);
}

void instantiate_collectible(t_gamedata *gamedata, int x, int y)
{
	void	*img;
	char *path;

	path = "./assets/collectibles/collectible1.xpm";
	img = mlx_xpm_file_to_image(gamedata->mlx, path, &gamedata->image_size, &gamedata->image_size);
	gamedata->collectible_object = img;
    mlx_put_image_to_window(gamedata->mlx, gamedata->mlx_window, img, x, y);
}

void instantiate_exit(t_gamedata *gamedata, int x, int y)
{
	void	*img;
	char *path;

	path = "./assets/exits/exit1.xpm";
	img = mlx_xpm_file_to_image(gamedata->mlx, path, &gamedata->image_size, &gamedata->image_size);
	gamedata->exit_object = img;
    mlx_put_image_to_window(gamedata->mlx, gamedata->mlx_window, img, x, y);
}

void get_object_path(t_gamedata *gamedata)
{
	char *path;

	if (gamedata->current_direction == 'W')
		path = "./assets/player/player_up.xpm";
	if (gamedata->current_direction == 'A')
		path = "./assets/player/player_left.xpm";
	if (gamedata->current_direction == 'S')
		path = "./assets/player/player_down.xpm";
	if (gamedata->current_direction == 'D')
		path = "./assets/player/player_right.xpm";
	gamedata->direction_path = path;
}

void instantiate_player_direction(t_gamedata *gamedata, void *img)
{
	if (gamedata->current_direction == 'W')
		gamedata->player_up_object = img;
	if (gamedata->current_direction == 'A')
		gamedata->player_left_object = img;
	if (gamedata->current_direction == 'S')
		gamedata->player_down_object = img;
	if (gamedata->current_direction == 'D')
		gamedata->player_right_object = img;
}

void instantiate_player(t_gamedata *gamedata, int x, int y)
{
	void	*img;

	img = mlx_xpm_file_to_image(gamedata->mlx, gamedata->direction_path, &gamedata->image_size, &gamedata->image_size);
	instantiate_player_direction(gamedata, img);
    mlx_put_image_to_window(gamedata->mlx, gamedata->mlx_window, img, x, y);
}


void instantiate_world(t_gamedata *gamedata, int x, int y, char object)
{
	if (object == '1')
		instantiate_wall(gamedata, x, y);
	if (object == 'P')
	{
		get_object_path(gamedata);
		instantiate_player(gamedata, x, y);
	}
	if (object == 'C')
		instantiate_collectible(gamedata, x, y);
	if (object == 'E')
		instantiate_exit(gamedata, x, y);
}

void get_initial_informations(t_gamedata *gamedata)
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
				gamedata->current_x = i;
				gamedata->current_y = j;
			}
			j++;
		}
		i++;
	}
}

void read_map(t_gamedata *gamedata)
{
    int fd;
    int file_length;
    char *map;
    
    file_length = get_file_length(gamedata);
    map = (char *)malloc(file_length + 1);
    fd = open(gamedata->map_destination, O_RDONLY);
    read(fd, map, file_length);
    gamedata->map = ft_split(map, '\n');

	get_initial_informations(gamedata);
    close(fd);
	free(map);
}

void render_map(t_gamedata *gamedata)
{
	int i = 0;
	int j;

	int x;
    int y;

	x = 0;
    y = 0;
	while (gamedata -> map[i])
	{
		j = 0;
		x = 0;
		while (gamedata -> map[i][j])
		{
			instantiate_world(gamedata, x, y, gamedata -> map[i][j]);
			x += 64;
			j++;
		}
	    y += 64;
		i++;
	}
}

void	player_movement(t_gamedata *gamedata, int current_x, int current_y)
{
	gamedata->map[gamedata->current_x][gamedata->current_y] = '0';
	gamedata->current_x = current_x;
	gamedata->current_y = current_y;
	gamedata->map[current_x][current_y] = 'P';
	mlx_clear_window(gamedata->mlx, gamedata->mlx_window);

	render_map(gamedata);
}

void	move_character_up(t_gamedata *gamedata)
{
	gamedata->current_direction = 'W';
	player_movement(gamedata, gamedata->current_x - 1, gamedata->current_y);
}

void	move_character_left(t_gamedata *gamedata)
{
	gamedata->current_direction = 'A';
	player_movement(gamedata, gamedata->current_x, gamedata->current_y - 1);
}

void	move_character_down(t_gamedata *gamedata)
{
	gamedata->current_direction = 'S';
	player_movement(gamedata, gamedata->current_x + 1, gamedata->current_y);
}

void	move_character_right(t_gamedata *gamedata)
{
	gamedata->current_direction = 'D';
	player_movement(gamedata, gamedata->current_x, gamedata->current_y + 1);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	exit_game(t_gamedata *gamedata, char *str, int exit_mode)
{
	if (str)
		printf("ERROR\n%s You left dude come back... ", str);
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

int key_event(int key, t_gamedata *gamedata)
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
		printf("You left dude come back...");
		exit_game(gamedata, NULL, 0);
	}
	return 0;
}

void game_init(t_gamedata *gamedata)
{
	void *mlx_window;
	void *mlx;

	mlx = mlx_init();
	gamedata->mlx = mlx;


	gamedata->window_width = 64 * get_line_size(gamedata);
	gamedata->window_height = 64 * get_line_count(gamedata);
	mlx_window = mlx_new_window(gamedata->mlx, gamedata->window_width, gamedata->window_height, "a");
	gamedata->mlx_window = mlx_window;
}

int main(int argc, char **argv)
{
    t_gamedata *gamedata;
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
    return 0;
}