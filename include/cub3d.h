/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 16:58:52 by kposthum      #+#    #+#                 */
/*   Updated: 2023/12/19 15:34:56 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <libft.h>
# include <math.h>
# include <stdbool.h>
# include <MLX42/MLX42.h>
# include <MLX42/MLX42_Int.h>
# include <glad/glad.h>
# include <KHR/khrplatform.h>
# include <lodepng/lodepng.h>

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

typedef struct	s_img_data
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;
}	t_img_data;

typedef struct s_cub3d
{
	t_data	**data;
	mlx_t	*mlx;
}	t_cub3d;


// err3d.c
void	errmsg(char *msg);
// parse3d.c
t_data	**parse_input(int count, char **arg);
// list3d.c
void	clear_list_pre(t_data **head);
void	clear_list_post(mlx_t *mlx, t_data **head);
t_data	*newnode(void *cont);
void	clear_node(t_data **head, t_data *node);
void	add_node(t_data **head, t_data *node);
void	set_flag_rest(t_data *node);
// map3d.c
bool	validate_map(t_data **head);
// color_texture3d.c
bool	validate_color(t_data **head, int flag);
bool	validate_texture(t_data **head, int flag);
// init3d.c
t_cub3d	*cub3d_init(mlx_t *mlx, t_data **head);
// destroy3d.c
void	destroy_cub3d(t_cub3d *cub3d);

#endif
