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

//SOOOOOOO_LONG
//
//
// void set_game_assets(t_gamedata *gamedata)
// {
// 	void *wall_image;

// 	gamedata->wall_path = "./assets/walls/wall1.xpm";
// }

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
	
	gamedata->wall_path = "./assets/walls/wall2.xpm";
	img = mlx_xpm_file_to_image(gamedata->mlx, gamedata->wall_path, &gamedata->image_size, &gamedata->image_size);
    mlx_put_image_to_window(gamedata->mlx, gamedata->mlx_window, img, x, y);
}

void instantiate_collectible(t_gamedata *gamedata, int x, int y)
{
	void	*img;
	
	gamedata->wall_path = "./assets/collectibles/collectible1.xpm";
	img = mlx_xpm_file_to_image(gamedata->mlx, gamedata->wall_path, &gamedata->image_size, &gamedata->image_size);
    mlx_put_image_to_window(gamedata->mlx, gamedata->mlx_window, img, x, y);
}

void instantiate_exit(t_gamedata *gamedata, int x, int y)
{
	void	*img;
	
	gamedata->wall_path = "./assets/exits/exit1.xpm";
	img = mlx_xpm_file_to_image(gamedata->mlx, gamedata->wall_path, &gamedata->image_size, &gamedata->image_size);
    mlx_put_image_to_window(gamedata->mlx, gamedata->mlx_window, img, x, y);
}

void instantiate_player(t_gamedata *gamedata, int x, int y)
{
	void	*img;
	
	gamedata->wall_path = "./assets/player/player_down.xpm";
	img = mlx_xpm_file_to_image(gamedata->mlx, gamedata->wall_path, &gamedata->image_size, &gamedata->image_size);
    mlx_put_image_to_window(gamedata->mlx, gamedata->mlx_window, img, x, y);
}

void instantiate_player_up(t_gamedata *gamedata, int x, int y)
{
	void	*img;
	gamedata->wall_path = "./assets/player/player_up.xpm";
	img = mlx_xpm_file_to_image(gamedata->mlx, gamedata->wall_path, &gamedata->image_size, &gamedata->image_size);
    mlx_put_image_to_window(gamedata->mlx, gamedata->mlx_window, img, x, y);
}

void instantiate_world(t_gamedata *gamedata, int x, int y, char object)
{
	if (object == '1')
		instantiate_wall(gamedata, x, y);
	// if (object == 'P')
	// {
	// 	instantiate_player(gamedata, x, y);
	// }
	if (object == 'C')
		instantiate_collectible(gamedata, x, y);
	if (object == 'E')
		instantiate_exit(gamedata, x, y);
}

void read_map(t_gamedata *gamedata)
{
    int fd;
    int file_length;
    char *map;
    
    file_length = get_file_length(gamedata);
    map = (char *)malloc(file_length + 1);
    fd = open(gamedata->map_destination, O_RDWR);
    read(fd, map, file_length);
    gamedata->map = ft_split(map, '\n');

    close(fd);
	free(map);
}
void print_map(t_gamedata *gamedata)
{
	int i;
	i= 0;
	while (gamedata -> map[i])
	{
	
		printf("%s",gamedata->map[i]);

		printf("\n");
		i++;
	}
}
void render_map(t_gamedata *gamedata,int key)
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
			if (gamedata -> map[i][j] == 'P')
			{
				gamedata->current_x = x;	// X posiotion of grafic 64 bit
				gamedata->current_y = y;	// Y Position of grafic 64 bit
				gamedata->map_coordinates_i = i; // x coordinate of map[i][j]
				gamedata->map_coordinates_j = j; // y cooridnate of map[i][j]
				printf("%d %d",gamedata->map_coordinates_i,gamedata->map_coordinates_j);
				if(key == 9999)
					instantiate_player(gamedata, x, y);
				if(key == W)
				{
					instantiate_player_up(gamedata, gamedata->current_x, gamedata->current_y);
					printf("y = %d",gamedata->current_y);
					
				}
				//printf("%d and %d",gamedata->current_x - 1,gamedata->current_y);
			} 
			x += 64;
			j++;
		}
	    y += 64;
		printf("\n");
		i++;
	}
}

// void player_movement(t_gamedata *gamedata)
// {
		
// }
	void player_move_up(t_gamedata *gamedata)
 	{	
  		gamedata->map[gamedata->map_coordinates_i - 1][gamedata->map_coordinates_j] = 'P'; // chage map Player posiotion
		gamedata->map[gamedata->map_coordinates_i][gamedata->map_coordinates_j] = '0'; // delete old Player Position
		
		
		print_map(gamedata);
	}

// void player_move_down(t_gamedata *gamedata)
// {
// 	gamedata->map[gamedata->current_x, gamedata->current_y + 1];
// }

// void player_move_left(t_gamedata *gamedata)
// {
// 	gamedata->map[gamedata->current_x - 1, gamedata->current_y];
// }

// void player_move_right(t_gamedata *gamedata)
// {
// 	gamedata->map[gamedata->current_x + 1, gamedata->current_y];
// }

int key_event(int key, t_gamedata *gamedata)
{
	if (key == W)
	{
		//move player up
		
		player_move_up(gamedata);
		mlx_clear_window(gamedata->mlx,gamedata->mlx_window); // delete old img
		render_map(gamedata,W);
		
	}
	printf("aa");
	return 0;
}


int main()
{
	void *mlx;
    void *mlx_window;

    mlx = mlx_init();
	
    t_gamedata *gamedata;
    gamedata = malloc(sizeof(t_gamedata));

	gamedata->map_destination = "./maps/map2.ber";
	gamedata->mlx = mlx;
	gamedata->window_width = 64 * get_line_size(gamedata);
	gamedata->window_height = 64 * get_line_count(gamedata);
	mlx_window = mlx_new_window(gamedata->mlx, gamedata->window_width, gamedata->window_height, "a");
	gamedata->mlx_window = mlx_window;
	read_map(gamedata);
	render_map(gamedata,9999);
	mlx_hook(gamedata->mlx_window, 2, 1L << 0, key_event, gamedata);
	mlx_loop(mlx);
    return 0;
}