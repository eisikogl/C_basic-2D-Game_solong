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
int get_file_length(t_gamedata *gamedata)
{
	char c;
	int i = 0;
    int fd;

    fd = open(gamedata->map_destination, O_RDONLY);
	while(read(fd, &c, 1))
		i++;
    close(fd);
	return i;
}

void read_map(t_gamedata *gamedata)
{
    int file_length;
    char **map;
    int fd;
    
    file_length = get_file_length(gamedata);
    map = (char **)malloc(file_length + 1);
    
    fd = open(gamedata->map_destination, O_RDONLY);
    read(fd, map, file_length);
    map[file_length + 1] = '\0';
    gamedata->map = ft_split(map, '\n');
    
    int i = 0;
	while (i < 4)
	{
		printf("string %d : %s\n", i, map[i]);
		i++;
	}
    close(fd);
}

void create_wall(t_gamedata *gamedata, int x, int y)
{
	void	*img;
	char	*relative_path = "./assets/walls/wall1.xpm";

	img = mlx_xpm_file_to_image(gamedata->mlx, relative_path, &gamedata->image_size, &gamedata->image_size);
    mlx_put_image_to_window(gamedata->mlx, gamedata->mlx_window, img, x, y);
}

void render_map(t_gamedata *gamedata)
{
    read_map(gamedata);
    // int i = 0;
    // int j = 0;
    // int x;
    // int y;

    // x = 0;
    // y = 0;
    // while (gamedata->map[i])
    // {
    //     // while (gamedata->map[i][j])
    //     // {
    //     //     printf("%c", gamedata->map[i][j]);
    //     //     //create_wall(gamedata, x, y);
    //     //     i++;
    //     // }
    //     printf("%c", gamedata->map[i][j]);
    //     x += 16;
    //     i++;
    // }
}

int main()
{
    t_gamedata *gamedata;
    gamedata = malloc(sizeof(t_gamedata));
    void *mlx;
    void *mlx_window;

    mlx = mlx_init();
    gamedata->mlx = mlx;
    gamedata->game_name = "so_long";
    gamedata->map_destination = "./maps/map1.ber";

    mlx_window = mlx_new_window(mlx, 1920, 1080, gamedata->game_name);
    gamedata->mlx_window = mlx_window;
    //render_map(gamedata);
    mlx_loop(mlx);
    
    //printf("%s", gamedata->map);
    return 0;
}