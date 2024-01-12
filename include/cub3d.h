#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <libft.h>
# include <math.h>
# include <stdbool.h>
# include <limits.h>
# include <float.h>
# include <MLX42/MLX42.h>
# include <MLX42/MLX42_Int.h>
# include <glad/glad.h>
# include <KHR/khrplatform.h>
# include <lodepng/lodepng.h>

# ifndef PI
#  define PI 3.14159265358979323846
# endif

# ifndef HEIGHT
#  define HEIGHT 900
# endif

# ifndef WIDTH
#  define WIDTH 1600
# endif

# ifndef BLOCKSIZE
#  define BLOCKSIZE 128
# endif

# ifndef STEPSIZE
#  define STEPSIZE 16
# endif

# ifndef RAYS
#  define RAYS 320
# endif

typedef enum e_flag
{
	C_COLOR = 1,
	F_COLOR,
	N_TEXTURE,
	E_TEXTURE,
	S_TEXTURE,
	W_TEXTURE,
	MAP_START,
}	t_flag;

typedef enum e_wall
{
	EAST = 0,
	SOUTH = 1,
	WEST = 2,
	NORTH = 3,
}	t_wall;

typedef struct s_data
{
	int				flag;
	void			*cont;
	struct s_data	*next;
	struct s_data	*prev;
}	t_data;

typedef struct s_location
{
	size_t	x;
	size_t	y;
}	t_location;

typedef struct s_img_data
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;
}	t_img_data;

typedef struct t_background
{
	int			r;
	int			g;
	int			b;
	mlx_image_t	*image;
}	t_background;

typedef struct s_ray
{
	float		len;
	float		corr_len;
	float		angle;
	float		x;
	float		y;
	float		wall_height;
	uint8_t		wall;
	mlx_image_t	*slice_old;
	mlx_image_t	*slice_new;
}	t_ray;

typedef struct s_player
{
	t_location	start;
	float		location[2];
	float		angle;
	float		dx;
	float		dy;
	float		plane_dist;
	t_ray		ray[RAYS];
}	t_player;

typedef	struct s_image
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;
	char			*filename;
}	t_image;

typedef struct s_map
{
	t_data	*flags;
	t_data	*map;
	int		size;
}	t_map;

typedef struct s_cub3d
{
	t_map		*map;
	mlx_t		*mlx;
	mlx_image_t	*ceiling;
	mlx_image_t	*floor;
	t_player	*player;
	t_data		**data;
	bool		moved;
}	t_cub3d;

// err3d.c
void		errmsg(char *msg);
// flag3d.c
void		assign_flag(t_data **head);
void		set_flag_rest(t_data *node);
bool		count_flag(t_data **head);
// list3d.c
t_data		*find_node(t_data **head, int flag);
t_data		*newnode(void *cont);
void		clear_node(t_data **head, t_data *node);
void		add_node(t_data **head, t_data *node);
// map3d.c
bool		validate_map(t_data **head);
// maputils3d.c
bool		player(char **map);
t_location	find_loc(char **map, char *arr);
// color_texture3d.c
bool		validate_color(t_data **head, int flag);
bool		validate_texture(t_data **head, int flag);
size_t		determine_height(t_data **start);
size_t		determine_length(t_data **start);
// init3d.c
bool		cub3d_init(t_cub3d *cub, mlx_t *mlx, t_map *data);
void		set_color(mlx_image_t *image, int *value, size_t size);
void		init_rays(t_player *player, char **map);
// destroy3d.c
void		destroy_cub3d(t_cub3d *cub3d);
void		clear_list_pre(t_data **head);
void		clear_list_two(t_data **head);
void		clear_list_three(t_data **head);
void		clear_list_post(mlx_t *mlx, t_data **head);
// utils3d.c
void		trim_nl(char *line);
// window3d.c
void		init_window(t_cub3d *cub3d);
void		draw_slices(mlx_t *mlx, t_player *player);
// keyhooks3d.c
void		move_player(mlx_key_data_t keydata, void *param);
// display3d.c
void		redisplay(t_cub3d *cub3d);
// ray3d.c
float		ray_len(t_player *player, size_t i, char **map);

int			ft_strmapiteri(char **arr, int (*f)(char *, int));
int			ft_access(char *filename);
int			ft_accesstype(char *filename, char *expected_type);
int			ft_isempty(char *str);
char		**read_from_file(int fd);
void		*ft_realloc(void *ptr, size_t oldsize, size_t size);
char		**import_map(char *filename);
char		*find_flag(char **arr, const char *flag_type);
int			is_flag(char *str);

int			check_map(char **map);
int			find_player(char *str, int index);
t_map		*read_map_from_file(char *filename);
int			validate_flag(char **arr, const char *flag_type);

bool		test_init(t_cub3d *cub, mlx_t *mlx, t_map *data);

#endif
