/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 16:58:52 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/10 15:39:42 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
#  define PI 3.14159265359
# endif

# ifndef HEIGHT
#  define HEIGHT 900
# endif

# ifndef WIDTH
#  define WIDTH 1600
# endif

# ifndef BLOCKSIZE
#  define BLOCKSIZE 100
# endif

# ifndef STEPSIZE
#  define STEPSIZE 10
# endif

# ifndef RAYS
#  define RAYS 160
# endif

typedef enum e_flag
{
	C_COLOR = 0,
	F_COLOR = 1,
	N_TEXTURE = 2,
	E_TEXTURE = 3,
	S_TEXTURE = 4,
	W_TEXTURE = 5,
	MAP_START = 6,
	TO_CLEAR = 7,
}	t_flag;

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
	mlx_image_t	*slice;
}	t_ray;

typedef struct s_player
{
	mlx_image_t	*test;
	t_location	start;
	float		location[2];
	float		angle;
	float		dx;
	float		dy;
	float		height;
	float		plane_dist;
	mlx_image_t	*raydot;
	t_ray		ray[RAYS];
}	t_player;

typedef struct s_cub3d
{
	t_data		**data;
	mlx_t		*mlx;
	mlx_image_t	*ceiling;
	mlx_image_t	*floor;
	t_player	*player;
	bool		moved;
}	t_cub3d;

// err3d.c
void		errmsg(char *msg);
// parse3d.c
t_data		**parse_input(int count, char **arg);
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
t_cub3d		*cub3d_init(mlx_t *mlx, t_data **head);
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
void		test(t_cub3d *cub3d);
void		test_draw_slices(mlx_t *mlx, t_player *player);
// keyhooks3d.c
float		calc_angle(float angle);
void		move_player(mlx_key_data_t keydata, void *param);
// display3d.c
void		redisplay(void *param);
// ray3d.c
float		ray_len(t_player *player, size_t i, char **map);
#endif
