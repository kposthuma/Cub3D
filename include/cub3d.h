/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 14:08:11 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/25 14:02:50 by cbijman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <libft.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <MLX42/MLX42.h>
# include <MLX42/MLX42_Int.h>
# include <glad/glad.h>
# include <KHR/khrplatform.h>
# include <lodepng/lodepng.h>
# include <cuberr.h>

# ifndef PI
#  define PI 3.14159265358979323846
# endif

# ifndef HEIGHT
#  define HEIGHT 900
# endif

# ifndef WIDTH
#  define WIDTH 1600
# endif

# ifndef BLOCK
#  define BLOCK 128
# endif

# ifndef STEPSIZE
#  define STEPSIZE 16
# endif

# ifndef MAX_FLAG_SIZE
#  define MAX_FLAG_SIZE 6
# endif

# ifndef FLT_MAX
#  define FLT_MAX 3.40282347e+38F
# endif

typedef enum e_flag
{
	N_TEXTURE = 0,
	E_TEXTURE = 1,
	S_TEXTURE = 2,
	W_TEXTURE = 3,
	C_COLOR,
	F_COLOR,
}	t_flag;

typedef enum e_mapflag
{
	MAP,
	FLAG,
	UNKNOWN_BUT_COOL
}	t_mapflag;

typedef enum e_direction
{
	NORTH	= 0,
	EAST	= 1,
	SOUTH	= 2,
	WEST	= 3,
}	t_direction;

typedef struct s_data
{
	char			*content;
	t_mapflag		flag;
	struct s_data	*next;
}	t_data;

typedef struct s_location
{
	size_t	x;
	size_t	y;
}	t_location;

typedef struct s_ray
{
	float		len;
	float		corr_len;
	float		angle;
	float		x;
	float		y;
	float		wall_ht;
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
	t_ray		*ray;
	size_t		raycount;
}	t_player;

typedef union u_wall
{
	struct
	{
		mlx_texture_t	*north;
		mlx_texture_t	*south;
		mlx_texture_t	*west;
		mlx_texture_t	*east;
	};
	mlx_texture_t		*direction[4];
}	t_wall;

typedef struct s_map
{
	t_wall		*walls;
	t_color		*floor;
	t_color		*ceiling;
	char		**map;
}	t_map;

typedef struct s_cub3d
{
	t_map		*map;
	mlx_t		*mlx;
	mlx_image_t	*ceiling;
	mlx_image_t	*floor;
	mlx_image_t	*screen;
	t_player	*player;
	bool		mouse;
}	t_cub3d;

// list.c
t_data		*find_node(t_data **head, t_mapflag flag);
t_data		*new_node(void *cont, t_mapflag flag);
void		clear_node(t_data **head, t_data *node);
void		add_node(t_data **head, t_data *node);
// maputils.c
t_location	find_loc(char **map, char *arr);
// color_utils.c
char		*ft_trim_whitespace(char *s);
void		ft_trimnl(char *str);
// init.c
bool		cub3d_init(t_cub3d *cub, mlx_t *mlx, t_map *data);
void		init_rays(mlx_image_t *screen, t_player *player, char **map);
// window.c
void		init_window(t_cub3d *cub3d);
// keyhooks.c
void		move_player(void *param);
void		turn_player(t_cub3d *cub3d, bool left);
// display.c
void		redisplay(t_cub3d *cub3d);
// ray.c
float		ray_len(t_player *player, size_t i, char **map);
// mouse.c
void		mouse(void *param);
void		disable(mlx_key_data_t keydata, void *param);

int			ft_strmapiteri(char **arr, int (*f)(char *, int));
int			ft_access(char *filename);
int			ft_accesstype(char *filename, char *expected_type);
int			ft_isempty(char *str);
char		**read_from_file(int fd);
char		**import_map(char *filename);
char		*find_flag(char **arr, const char *flag_type);
int			is_flag(char *str);

int			check_map(char **map);
int			find_player(char **str);
t_map		*read_map_from_file(char *filename);
int			validate_flag(char **arr, const char *flag_type);

void		set_colorc(mlx_image_t *image, t_color *color, size_t size);
void		ft_free(char **arg);
void		free_cub3d(t_cub3d *cub);
void		free_player(t_player *player);
void		free_map(t_map	*map);

float		collision_up(t_player *player, size_t i, char **map);
float		collision_down(t_player *player, size_t i, char **map);
float		collision_right(t_player *player, size_t i, char **map);
float		collision_left(t_player *player, size_t i, char **map);
void		determine_wall(t_player *player, size_t i, float x, float y);

t_data		*read_map_to_struct(int fd);
int	count_flags(t_data **head, t_mapflag type);

#endif
